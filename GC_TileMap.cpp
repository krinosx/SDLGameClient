#include "GC_TileMap.h"

GC_TileMap::GC_TileMap(std::string id)
{
	this->id = id;
}

GC_TileMap::~GC_TileMap()
{
}

std::shared_ptr<GC_Tile> GC_TileMap::getTile(unsigned short tileId)
{
	return  (this->tileMap.count(tileId) == 1) ? this->tileMap[tileId] : nullptr;
}

bool GC_TileMap::loadMap(std::string mapName)
{
	std::cout << "Load a map from the disc. Noy yet implemented!" << std::endl;
	return true;
}
