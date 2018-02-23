#include "GC_Scene_Menu.h"



GC_Scene_Menu::GC_Scene_Menu(std::string id)
	:GC_Scene(id)
{
	this->isLoaded = false;
}


GC_Scene_Menu::~GC_Scene_Menu()
{
	this->unload();
	std::cout << "Destroying GC_Scene_Menu. " << std::endl;
}

void GC_Scene_Menu::draw(SDL_Renderer * renderer)
{

	this->guiManager.draw(renderer);

}

void GC_Scene_Menu::load(SDL_Renderer * renderer)
{

	SDL_Texture * bgImage = this->sceneManager.lock()->getResourceLoader()->getTexture("menu_bg_1")->getTexture().get();
	SDL_Texture * menuFrameBg = this->sceneManager.lock()->getResourceLoader()->getTexture("menu_frame_opaque")->getTexture().get();

	SDL_Texture * button_connect_red = this->sceneManager.lock()->getResourceLoader()->getTexture("button_connect_red")->getTexture().get();
	SDL_Texture * button_connect_green = this->sceneManager.lock()->getResourceLoader()->getTexture("button_connect_green")->getTexture().get();

	SDL_Texture * button_configure_red = this->sceneManager.lock()->getResourceLoader()->getTexture("button_config_red")->getTexture().get();
	SDL_Texture * button_configure_green = this->sceneManager.lock()->getResourceLoader()->getTexture("button_config_green")->getTexture().get();

	SDL_Texture * button_quit_red = this->sceneManager.lock()->getResourceLoader()->getTexture("button_quit_red")->getTexture().get();
	SDL_Texture * button_quit_green = this->sceneManager.lock()->getResourceLoader()->getTexture("button_quit_green")->getTexture().get();


	SDL_Texture * textField_bg_editing = this->sceneManager.lock()->getResourceLoader()->getTexture("textfield_bg_opaque")->getTexture().get();
	SDL_Texture * textField_bg = this->sceneManager.lock()->getResourceLoader()->getTexture("textfield_bg_alpha50")->getTexture().get();

	SDL_Texture * connect_frame_bg = this->sceneManager.lock()->getResourceLoader()->getTexture("menu_connect_frame_opaque")->getTexture().get();
	
	SDL_Texture * button_connect_1 = this->sceneManager.lock()->getResourceLoader()->getTexture("button_connect")->getTexture().get();
	SDL_Texture * button_connect_1_clicked = this->sceneManager.lock()->getResourceLoader()->getTexture("button_connect_clicked")->getTexture().get();

	SDL_Texture * button_cancel_1 = this->sceneManager.lock()->getResourceLoader()->getTexture("button_cancel")->getTexture().get();
	SDL_Texture * button_cancel_1_clicked = this->sceneManager.lock()->getResourceLoader()->getTexture("button_cancel_clicked")->getTexture().get();




	this->mainPanel = new GUIPanel(0, 0, 1920 , 1080 );
	this->mainPanel->setId("MainPanel-BGImage");
	this->mainPanel->setBackgroundImage(bgImage);
	this->mainPanel->setOpaque(true);
	
	TTF_Font * font = this->sceneManager.lock()->getResourceLoader()->getFont("font_arial")->getFont();
	
	SDL_Color buttonColor = { 255,255,255,255 };
	SDL_Color buttonBgColor = { 155,255,155,125 };

	int xMiddle = (1920 / 2) - (800 / 2);
	int yMiddle = (1080 / 2) - (680 / 2);
	this->menuFramePanel = new GUIPanel(xMiddle, yMiddle, 800, 680);
	this->menuFramePanel->setOpaque(true);
	this->menuFramePanel->setDrawBgColor(false);
	this->menuFramePanel->setBackgroundImage(menuFrameBg);
	


	this->connect = new GUIButton(138, 80, 526, 159, "", font, false);
	this->connect->setDrawBgColor(false);
	this->connect->setBackgroundImage(button_connect_red);
	this->connect->setClickedImage(button_connect_green);
	this->connect->setAction([=]() {
		//this->sceneManager.lock()->loadScene("scene_loading");	
		this->menuFramePanel->hide();
		this->panelLogin->show();
	});
		
	
	this->configure = new GUIButton(138, 260, 526, 159, "", font, false);
	this->configure->setDrawBgColor(false);
	this->configure->setBackgroundImage(button_configure_red);
	this->configure->setClickedImage(button_configure_green);
	
	
	this->quitButton = new GUIButton(138, 440, 526, 159, "", font, true);
	this->quitButton->setDrawBgColor(false);
	this->quitButton->setBackgroundImage(button_quit_red);
	this->quitButton->setClickedImage(button_quit_green);	
	this->quitButton->setAction([=]() {
		this->sceneManager.lock()->notifyExit();
	});


	this->menuFramePanel->addComponent(this->configure);
	this->menuFramePanel->addComponent(this->connect);
	this->menuFramePanel->addComponent(this->quitButton);

	this->mainPanel->addComponent(this->menuFramePanel);
			
	

	int panelLoginX = (1920/ 2) - (512 / 2);
	int panelLoginY = (1080 / 2) - (512 / 2);

	this->panelLogin = new GUIPanel(panelLoginX, panelLoginY, 512, 512);
	this->panelLogin->setOpaque(true);
	this->panelLogin->setBackgroundImage(connect_frame_bg);


	this->usernameTextfield = new GUITextField(64, 132, 384, 56,"", font, false);
	this->usernameTextfield->setBackgroundImage(textField_bg);
	this->usernameTextfield->setBackgroundImageEditing(textField_bg_editing);
	this->usernameTextfield->setAction([&] {
		this->guiManager.setActiveInputTextComponent(this->usernameTextfield);
	});


	this->passwordTextfield = new GUITextField(64, 246, 384, 56, "", font, true);
	this->passwordTextfield->setLabelColor(buttonColor);
	this->passwordTextfield->setBackgroundImage(textField_bg);
	this->passwordTextfield->setBackgroundImageEditing(textField_bg_editing);
	this->passwordTextfield->setIsPassword(true);
	this->passwordTextfield->setAction([&] {
		this->guiManager.setActiveInputTextComponent(this->passwordTextfield);
	});



	this->connectButton = new GUIButton(265, 335, 180, 100, "", font, false);
	this->connectButton->setDrawBgColor(false);
	this->connectButton->setBackgroundImage(button_connect_1);
	this->connectButton->setClickedImage(button_connect_1_clicked);
	this->connectButton->setAction([&]() {
		std::cout << "Connect: User->" << this->usernameTextfield->getText() << " Pass->" << this->passwordTextfield->getText() << std::endl;
		this->networkClient.lock()->connect("localhost", (Uint16)5000);
		this->panelLogin->hide();
		this->sceneManager.lock()->loadScene("scene_main");
	});

	this->cancelConnectButton= new GUIButton(64, 335, 180, 100, "", font, true);
	this->cancelConnectButton->setDrawBgColor(false);
	this->cancelConnectButton->setBackgroundImage(button_cancel_1);
	this->cancelConnectButton->setClickedImage(button_cancel_1_clicked);
	this->cancelConnectButton->setAction([&]() {
		std::cout << "Cancel Connect - Back to Menu," << std::endl;
		this->panelLogin->hide();
		this->menuFramePanel->show();
	});


	this->panelLogin->addComponent(this->connectButton);
	this->panelLogin->addComponent(this->cancelConnectButton);
	this->panelLogin->addComponent(this->usernameTextfield);
	this->panelLogin->addComponent(this->passwordTextfield);
	
	this->mainPanel->addComponent(this->panelLogin);

	//this->guiManager.addComponent(this->panelLogin);
	this->guiManager.addComponent(mainPanel);
	this->panelLogin->hide();

	this->isLoaded = true;
}

void GC_Scene_Menu::unload()
{
	this->guiManager.destroy();
	this->isLoaded = false;
}

bool GC_Scene_Menu::isReady()
{
	return this->isLoaded;
}

void GC_Scene_Menu::processEvents(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_QUIT:
		break;
	case SDL_KEYDOWN:
		this->guiManager.keyPress(e.key.keysym);
		break;
	case SDL_KEYUP:
		this->guiManager.keyRelease(e.key.keysym);
		
		break;
	case SDL_MOUSEBUTTONDOWN:
		/* Dispatch the events for GUIManager */
		this->guiManager.click(e.button.x, e.button.y);
		break;
	case SDL_MOUSEBUTTONUP:
		this->guiManager.release(e.button.x, e.button.y);
		break;
	case SDL_TEXTEDITING:
		break;
	case SDL_TEXTINPUT:
		this->guiManager.textInput(e.text);
		break;
	default:
		break;
	}
	//std::cout << "Scene Menu Processing Events: " << std::endl;
	
}

void GC_Scene_Menu::setManager(std::weak_ptr<GC_SceneManager> manager)
{
	this->sceneManager = manager;
}

void GC_Scene_Menu::setNetworkClient(std::shared_ptr<Client> client)
{
	this->networkClient = client;
}
