#pragma once
#include "GC_Tile.h"
#include  <unordered_map>
class GC_TileMap
{

private:
	std::unordered_map<unsigned short, std::shared_ptr<GC_Tile>> tileMap;
	std::string mapName;
	std::string filePath;
	std::string id;
public:
	GC_TileMap(std::string id);
	~GC_TileMap();

	std::shared_ptr<GC_Tile> getTile(unsigned short);
	bool loadMap(std::string mapName);


};

