#pragma once
#include "GC_IResource.h"
#include <SDL.h>
class GC_Texture :
	public GC_IResource
{

private:
	std::string path;
	std::shared_ptr<SDL_Texture> texture;
	SDL_Rect size;
protected:
	virtual bool isReadyToLoad();

public:
	GC_Texture(std::string id, std::string path);
	~GC_Texture();

	bool loadTexture(SDL_Renderer * renderer);
	std::shared_ptr<SDL_Texture> getTexture();
	SDL_Rect getSize();
};

