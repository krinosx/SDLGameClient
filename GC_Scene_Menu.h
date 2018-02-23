#pragma once

#include <memory>
#include <GUIManager.h>
#include <GUIButton.h>
#include <GUIPanel.h>
#include <GUITextField.h>

#include <Client.h>

#include "GC_Scene.h"
#include "GC_SceneManager.h"


class GC_Scene_Menu :
	public GC_Scene
{

private:
	std::weak_ptr<GC_SceneManager> sceneManager;
	GUIManager guiManager;
	
	GUIPanel * mainPanel;
	
	GUIPanel * menuFramePanel;

	GUIButton * configure;
	GUIButton * connect;
	GUIButton * quitButton;

	GUIPanel * panelLogin;
	GUITextField * usernameTextfield;
	GUITextField * passwordTextfield;
	GUIButton * connectButton;
	GUIButton * cancelConnectButton;

	bool isLoaded = false;


	std::weak_ptr<Client> networkClient;

public:
	GC_Scene_Menu(std::string id);
	~GC_Scene_Menu();

	void draw(SDL_Renderer * renderer);
	void load(SDL_Renderer * renderer);
	void unload();
	bool isReady();
	void processEvents(SDL_Event e);
	void setManager(std::weak_ptr<GC_SceneManager> manager);
	void setNetworkClient(std::shared_ptr<Client> client);
};
