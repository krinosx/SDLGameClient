#include "GC_ResourceLoader.h"
#include <SDL.h>
#include <SDL_image.h>

GC_ResourceLoader::GC_ResourceLoader()
{
}


GC_ResourceLoader::~GC_ResourceLoader()
{
}

bool GC_ResourceLoader::loadFont(std::string id, std::string path, int size)
{
	std::shared_ptr<GC_Font> loadingFont(new GC_Font(id, path, size));

	if (loadingFont->loadResource())
	{
		this->fountList[loadingFont->getId()] = loadingFont;
		return true;
	}
	return false;
}

std::shared_ptr<GC_Font> GC_ResourceLoader::getFont(std::string fontName)
{
	return this->fountList[fontName];
}

bool GC_ResourceLoader::loadTexture(std::string id, std::string path, SDL_Renderer * renderer)
{
	
	std::shared_ptr<GC_Texture> texture(new GC_Texture(id, path));
	texture->loadTexture(renderer);

	this->imageList[texture->getId()] = texture;
	
	return true;
}

std::shared_ptr<GC_Texture> GC_ResourceLoader::getTexture(std::string textureName)
{
	return this->imageList.count(textureName) > 0 ? this->imageList[textureName] : nullptr;
}

void GC_ResourceLoader::unloadAll()
{
	this->fountList.clear();
	this->imageList.clear();
}
