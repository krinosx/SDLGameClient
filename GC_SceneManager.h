#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "GC_Scene.h"
#include "GC_ResourceLoader.h"
class GC_SceneManager : public std::enable_shared_from_this<GC_SceneManager>
{
private:
	std::unordered_map<std::string, std::weak_ptr<GC_Scene>> sceneList;
	std::weak_ptr<GC_Scene> activeScene;
	std::shared_ptr<GC_ResourceLoader> resourceLoader;

	std::weak_ptr<GC_Scene> sceneToLoad;
	void processSceneLoad(SDL_Renderer * renderer);


public:
	GC_SceneManager(std::shared_ptr<GC_ResourceLoader> loader);
	~GC_SceneManager();

	enum STATE { LOADING, RUNNING, EXIT };
	STATE currentState = LOADING;

	void loadScene(std::string scene);
	void unloadScene(std::string scene);
	void registerScene(std::string scene, std::shared_ptr<GC_Scene>);
	
	void unregisterScene(std::string scene);
	void unregisterScene(std::shared_ptr<GC_Scene>);

	std::weak_ptr<GC_Scene> getCurrentScene();
	std::shared_ptr<GC_ResourceLoader> getResourceLoader();


	void update(SDL_Renderer * renderer);

	void notifyExit();
};

