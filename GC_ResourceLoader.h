#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <unordered_map>
#include "GC_IResource.h"
#include "GC_Font.h"
#include "GC_Texture.h"

class GC_ResourceLoader
{
private:
	std::unordered_map<std::string, std::shared_ptr<GC_Font>> fountList;
	std::unordered_map<std::string, std::shared_ptr<GC_Texture>> imageList;


public:
	GC_ResourceLoader();
	~GC_ResourceLoader();

	bool loadFont(std::string id, std::string path, int size);
	std::shared_ptr<GC_Font> getFont(std::string fontName);

	bool loadTexture(std::string id, std::string path, SDL_Renderer * renderer);
	std::shared_ptr<GC_Texture> getTexture(std::string fontName);
	

	void unloadAll();
};

