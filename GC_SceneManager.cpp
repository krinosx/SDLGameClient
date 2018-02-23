#include "GC_SceneManager.h"
#include "GC_Scene.h"
#include "GC_Scene_Menu.h"
#include "GC_Scene_Loading.h"


void GC_SceneManager::processSceneLoad(SDL_Renderer * renderer)
{
	if (!this->sceneToLoad.expired()) {
		if (!this->sceneToLoad.lock()->isReady())
		{
			this->sceneToLoad.lock()->load(renderer);
		}

		if (!this->activeScene.expired()) {
			this->activeScene.lock()->unload();
		}
		this->activeScene = this->sceneToLoad;

		this->sceneToLoad.reset();
	}
}

GC_SceneManager::GC_SceneManager(std::shared_ptr<GC_ResourceLoader> loader)
{	
	this->resourceLoader = loader;
}

GC_SceneManager::~GC_SceneManager()
{
	std::cout << "Destroying GC_SceneManager." << std::endl;
	this->activeScene.reset();
	this->sceneList.clear();
}

void GC_SceneManager::loadScene(std::string scene)
{

	// Scene does not exist
	if (this->sceneList.count(scene) <= 0)
	{
		// load an error scene?
		return;
	}

	this->sceneToLoad = this->sceneList[scene];
}

void GC_SceneManager::unloadScene(std::string scene)
{
	this->activeScene.reset();
}

void GC_SceneManager::registerScene(std::string sceneName, std::shared_ptr<GC_Scene> scene)
{
	this->sceneList[sceneName] = scene;
}

void GC_SceneManager::unregisterScene(std::string scene)
{
	this->sceneList.erase(scene);
}

void GC_SceneManager::unregisterScene(std::shared_ptr<GC_Scene> sceneObj)
{
	this->sceneList.erase(sceneObj->getId());
}

std::weak_ptr<GC_Scene> GC_SceneManager::getCurrentScene()
{
	return this->activeScene;
}

std::shared_ptr<GC_ResourceLoader> GC_SceneManager::getResourceLoader()
{
	return this->resourceLoader;
}

void GC_SceneManager::update(SDL_Renderer * renderer)
{

	this->processSceneLoad(renderer);
}

void GC_SceneManager::notifyExit()
{
	this->currentState = EXIT;
}
