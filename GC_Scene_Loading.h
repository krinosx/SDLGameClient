#pragma once
#include "GC_Scene.h"
#include <memory>
#include "GC_SceneManager.h"
#include "GUIManager.h"
#include "GUIButton.h"
class GC_Scene_Loading :
	public GC_Scene
{

private:
	std::weak_ptr<GC_SceneManager> sceneManager;
	GUIManager guiManager;
	GUIButton * exitButton;
	
	bool isLoaded = false;

public:
	GC_Scene_Loading(std::string id);
	~GC_Scene_Loading();
	
	void draw(SDL_Renderer * renderer);
	void load(SDL_Renderer * renderer);
	void unload();
	bool isReady();
	void processEvents(SDL_Event e);
	void setManager(std::weak_ptr<GC_SceneManager> manager);
};

