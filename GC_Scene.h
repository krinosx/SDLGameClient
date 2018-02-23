#pragma once
#include <SDL.h>
#include <string>

class GC_Scene
{
protected:
	std::string id;
public:
	GC_Scene(std::string id);
	~GC_Scene();

	std::string getId();
	virtual void draw(SDL_Renderer * renderer) = 0;
	virtual void load(SDL_Renderer * renderer) = 0;
	virtual void unload() = 0;
	virtual bool isReady() = 0;
	virtual void processEvents(SDL_Event e) = 0;
};

