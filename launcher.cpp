#include <iostream>
#include <memory>

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#define FONT_LOCATION "/Library/Fonts/Arial.ttf"
#elif defined _WIN32 || _WIN64
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_net.h>
#define FONT_LOCATION "C:/Windows/Fonts/Arial.ttf"
#endif

#include <Client.h>

#include <GUIManager.h>
#include "GC_ResourceLoader.h"
#include "GC_SceneManager.h"
#include "GC_Scene_Menu.h"
#include "GC_Scene_Loading.h"
#include "GC_Configuration.h"
#include "GC_Scene_Main.h"
/*
 * Auxiliary function declaration
 */
void checkSDLError(int);
void processMessages(Message * message);

int main(int argc, char* argv[])
{
	bool isAppRunning = true;

	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	SDL_Event sdlEvent;


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		checkSDLError(__LINE__);
		exit(-1);
	}

	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init error, Unable to load TTF library: " << TTF_GetError() << std::endl;
		exit(-1);
	}
	
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) != (int)(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) {
		std::cout << "Unable to init Image Library: " << IMG_GetError() << std::endl;
	};

	if (SDLNet_Init() != 0)
	{
		std::cout << "Could not Init SDL_net: " << SDLNet_GetError() << std::endl;
		exit(2);
	}


	window = SDL_CreateWindow("AppWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);

	if (window == NULL)
	{
		std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
		exit(-1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		exit(-1);
	}
	/* Set the render to draw transparency*/
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	
	/*
	 CREATE SDL WINDOW AND INIT SUBSYSTEM - END
	*/

	/*
	 * INIT APP SPECIFIC SYSTEMS 
	 */

	/*
	* Network Subsystem
	*/
	std::shared_ptr<Client> networkClient(new Client());
	//std::vector<std::shared_ptr<Message>> networkMessages;
	std::vector<Message*> networkMessages;


	/*
	* Scene Manager Subsystem
	*/
	// TODO: Develop Scens subsystem
	std::shared_ptr<GC_ResourceLoader> resourceLoader = std::make_shared<GC_ResourceLoader>();
	resourceLoader->loadFont("font_arial", "E:\\Projetos\\assets\\arial.ttf", 32);


	/*
	* Load menu Images
	*/
	resourceLoader->loadTexture("menu_frame_opaque", IMG_MENU_FRAME_OPAQUE, renderer);
	resourceLoader->loadTexture("menu_frame_alpha60", IMG_MENU_FRAME_ALPHA60, renderer);

	resourceLoader->loadTexture("button_connect_red", IMG_MENU_BUTTON_CONNECT_RED, renderer);
	resourceLoader->loadTexture("button_connect_green", IMG_MENU_BUTTON_CONNECT_GREEN, renderer);

	resourceLoader->loadTexture("button_config_red", IMG_MENU_BUTTON_CONNECT_RED, renderer);
	resourceLoader->loadTexture("button_config_green", IMG_MENU_BUTTON_CONNECT_GREEN, renderer);

	resourceLoader->loadTexture("button_quit_red", IMG_MENU_BUTTON_QUIT_RED, renderer);
	resourceLoader->loadTexture("button_quit_green", IMG_MENU_BUTTON_QUIT_GREEN, renderer);
	
	resourceLoader->loadTexture("menu_bg_1", IMG_MENU_BG, renderer);


	resourceLoader->loadTexture("button_cancel", IMG_MENU_BUTTON_CANCEL, renderer);
	resourceLoader->loadTexture("button_cancel_clicked", IMG_MENU_BUTTON_CANCEL_CLICKED, renderer);

	resourceLoader->loadTexture("button_connect", IMG_MENU_BUTTON_CONNECT_1, renderer);
	resourceLoader->loadTexture("button_connect_clicked", IMG_MENU_BUTTON_CONNECT_1_CLICKED, renderer);

	resourceLoader->loadTexture("menu_connect_frame_opaque", IMG_MENU_FRAME_CONNECT, renderer);
	resourceLoader->loadTexture("menu_connect_frame_alpha30", IMG_MENU_FRAME_CONNECT_ALPHA30, renderer);

	resourceLoader->loadTexture("textfield_bg_opaque", IMG_MENU_TEXTFIELD_OPAQUE, renderer);
	resourceLoader->loadTexture("textfield_bg_alpha50", IMG_MENU_TEXTFIELD_ALPHA50, renderer);
	


	std::shared_ptr<GC_SceneManager> sceneManager = std::make_shared<GC_SceneManager>(resourceLoader);
	// Create scene and register in the sceneManager
	std::shared_ptr<GC_Scene_Menu> menuScene = std::make_shared<GC_Scene_Menu>("scene_menu");
	menuScene->setNetworkClient(networkClient);
	menuScene->setManager(sceneManager);
	sceneManager->registerScene(menuScene->getId(), menuScene);
	
	std::shared_ptr<GC_Scene_Loading> loading = std::make_shared<GC_Scene_Loading>("scene_loading");
	sceneManager->registerScene(loading->getId(), loading);
	loading->setManager(sceneManager);


	std::shared_ptr<GC_Scene_Main> mainScene = std::make_shared<GC_Scene_Main>("scene_main");
	sceneManager->registerScene(mainScene->getId(), mainScene);
	mainScene->setSceneManager(sceneManager);

	sceneManager->loadScene("scene_menu");
	
	/*
	* INI APP SPECIFIC SYSTEMS - END
	*/


	/*
	* MAIN EVENT LOOP
	*/
	while (isAppRunning)
	{

		/*
		* Pick Network Events
		*/
		if (networkClient->isConnected())
		{
			networkMessages = networkClient->checkForMessages();

			for (Message * message : networkMessages)
			{
				processMessages(message);
			}

			// Dealocate messages
			while (!networkMessages.empty())
			{
				auto * message = networkMessages.back();
				delete message;
				networkMessages.pop_back();
			}
			networkMessages.clear();
		}


		sceneManager->update(renderer);

		if (sceneManager->currentState == GC_SceneManager::EXIT)
		{
			isAppRunning = false;
			std::cout << "Scene manager notified an Exit action " << std::endl;
		}

		/*
		* Render the updated model
		*/
		SDL_RenderClear(renderer);

		/*
		* Draw the GUIManager as last component if you wish
		* it to be displayed at top of other rendering
		*/
		//manager.draw(renderer);
//		guiManager.draw(renderer);

		sceneManager->getCurrentScene().lock()->draw(renderer);
		//SDL_RenderCopy(sdlRenderer, textfieldBg, &textureRect, &textureRect);
		SDL_RenderPresent(renderer);

		/*
		* Deal with user input (basic create and send a message to server)
		*/
		while (SDL_PollEvent(&sdlEvent))
		{

			sceneManager->getCurrentScene().lock()->processEvents(sdlEvent);

			switch (sdlEvent.type)
			{
			case SDL_QUIT:
				isAppRunning = false;
				break;
			case SDL_KEYDOWN:
				//manager.keyPress(sdlEvent.key.keysym);
				//keyPressed(sdlEvent);
				break;
			case SDL_KEYUP:
				//guiManager.keyRelease(sdlEvent.key.keysym);
				//keyReleased(sdlEvent);
				break;
			case SDL_MOUSEBUTTONDOWN:
				/* Dispatch the events for GUIManager */
				//guiManager.click(sdlEvent.button.x, sdlEvent.button.y);
				//mousePressed(sdlEvent);
				if (networkClient->isConnected())
				{
					
					std::string message("Clicked: x");
					message.append(std::to_string(sdlEvent.button.x));
					message.append(" y=");
					message.append(std::to_string(sdlEvent.button.y));
					message.push_back('\n');
					
					networkClient->sendMessage(message);

				}

				break;
			case SDL_MOUSEBUTTONUP:
				//guiManager.release(sdlEvent.button.x, sdlEvent.button.y);
				//mouseReleased(sdlEvent);
				break;
			case SDL_TEXTEDITING:
				break;
			case SDL_TEXTINPUT:
				//std::cout << "Text: " << sdlEvent.text.text << std::endl;
				//manager.textInput(sdlEvent.text);
				break;
			default:
				break;
			}
		}		
	}

	/*
	* MAIN EVENT LOOP - END
	*/

	if (networkClient->isConnected())
	{
		networkClient->disconnect();
	}

	// Unload all resources
	resourceLoader->unloadAll();
	
	//loader->unloadAll();

	sceneManager.reset();
	menuScene.reset();

	TTF_Quit();
	IMG_Quit();
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;

}

void processMessages(Message * message)
{
	std::cout << "Implementar processamento de mensagem: " << message->getMessage() << std::endl;
}

void checkSDLError(int line = -1)
{
#ifndef NDEBUG
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		printf("SDL Error: %s\n", error);
		if (line != -1) {
			printf(" + line: %i\n", line);
		}
		SDL_ClearError();
	}
#endif
}