#include "GC_Texture.h"
#include <SDL_image.h>


bool GC_Texture::isReadyToLoad()
{
	return !this->id.empty() && !this->path.empty();
}

GC_Texture::GC_Texture(std::string id, std::string path)
	:GC_IResource(), path(path)
{
	this->setId(id);
}

GC_Texture::~GC_Texture()
{
}

bool GC_Texture::loadTexture(SDL_Renderer * renderer)
{

	if (!this->isReadyToLoad())
	{// Todo inform about the error/constraints
		return false;
	}

	SDL_Surface *surface = IMG_Load(path.c_str());
		if (!surface)
	{
		std::cout << "Error loading image[ id=" << id << " File=" << path << "] Error = " << IMG_GetError() << std::endl;
		return false;
	}

	this->size.x = 0;
	this->size.y = 0;
	this->size.w = surface->w;
	this->size.h = surface->h;

	SDL_Texture *loadingTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_SetTextureBlendMode(loadingTexture, SDL_BLENDMODE_BLEND);

	SDL_FreeSurface(surface);

	if (loadingTexture != NULL) {
		this->texture = std::shared_ptr<SDL_Texture>(loadingTexture, [=](SDL_Texture * texture) {
			std::cout << "Destroying texture: " << this->getId();
			SDL_DestroyTexture(texture);
			std::cout << " ... Done." << std::endl;
		});
		return true;
	}

	return false;
}

std::shared_ptr<SDL_Texture> GC_Texture::getTexture()
{
	if (this->texture)
	{
		return this->texture;
	}
	return nullptr;
}

SDL_Rect GC_Texture::getSize()
{
	return this->size;
}
