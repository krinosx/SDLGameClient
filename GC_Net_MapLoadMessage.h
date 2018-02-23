#pragma once
#include <iostream>
#include <string>
#include <vector>
class GC_Net_MapLoadMessage
{

private:
	std::string mapId;
	std::string tileMapId;
	unsigned char width;
	unsigned char height;
	unsigned char numLayers;
	std::vector<unsigned short> tileList;

	bool parseMessage();
public:
	GC_Net_MapLoadMessage(std::string message);
	~GC_Net_MapLoadMessage();
};

