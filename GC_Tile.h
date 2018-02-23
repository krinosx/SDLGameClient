#pragma once
#include <memory>
#include <SDL.h>
#include "GC_Texture.h"
/*
 An object to represent a portion of the screen.
 Usually a tile may represent a square portion of the map, like an Item 
 or an object like a wall, a door, etc.

 In this architecture the Tile will only be a visual representation as all the
 logic will be processed on the server side.
*/
class GC_Tile
{

private:
	unsigned short id; // max 65.000 ids (2 bytes)
	int posX; // check if its needed
	int posY; // check if its needed
	int height;
	int width;
	SDL_Rect drawingRect;
	std::shared_ptr<GC_Texture> texture;
	
public:
	GC_Tile(unsigned short id, int x, int y, int w, int h, std::shared_ptr<GC_Texture> texture);
	~GC_Tile();

	void draw(SDL_Renderer * renderer);
	unsigned short getId();
};

