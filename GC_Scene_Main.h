#pragma once
#include "GC_Scene.h"
#include <GUIManager.h>
#include "GC_SceneManager.h"
#include <memory>
#include "GC_Configuration.h"

class GC_Scene_Main :
	public GC_Scene
{
private:
	std::weak_ptr<GC_SceneManager> sceneManager;
	SDL_Texture * bgTexture;
	GUIManager guiManager;

public:
	GC_Scene_Main(std::string id);
	~GC_Scene_Main();

	void setSceneManager(std::shared_ptr<GC_SceneManager> sceneManager);


	/*GC_Scene virtual methods*/
	void draw(SDL_Renderer * renderer);
	void load(SDL_Renderer * renderer);
	void unload();
	bool isReady();
	void processEvents(SDL_Event e);

};

