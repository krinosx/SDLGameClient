#include "GC_Tile.h"


GC_Tile::GC_Tile(unsigned short id, int x, int y, int w, int h, std::shared_ptr<GC_Texture> texture)
	: id(id), posX(x), posY(y), texture(texture), width(w), height(h)
{
	this->drawingRect = { this->posX, this->posY, this->width, this->height };
}

GC_Tile::~GC_Tile()
{
}

void GC_Tile::draw(SDL_Renderer * renderer)
{
	SDL_RenderCopy(renderer, this->texture->getTexture().get(), &this->texture->getSize(), &this->drawingRect);
}

unsigned short GC_Tile::getId()
{
	return this->id;
}
