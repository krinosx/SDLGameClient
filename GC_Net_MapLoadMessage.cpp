#include "GC_Net_MapLoadMessage.h"

int readIntByte(std::string *message, unsigned int pos) {

	if (pos < (*message).size())
	{
		unsigned char value = (*message)[pos];
		return (int)value;
	} 
	else
	{
		return -1;
	}
}

unsigned short readShortByte(std::string * message, unsigned int startPos)
{
	if (startPos < ((*message).size()-1) )
	{
		unsigned short value = (*message)[startPos] << 8;
		value = value | (*message)[startPos + 1];
		return value;
	}
	else
	{
		return -1;
	}

}

bool GC_Net_MapLoadMessage::parseMessage()
{
	return false;
}

GC_Net_MapLoadMessage::GC_Net_MapLoadMessage(std::string message)
{
	/*
		messageFormat

		[0] msgSize
		[1] msgSize
		[2] msg_type = MAP_LOAD
		[3] map_id
		[4] width
		[5] height
		[6] num_layers
		[7] tile_id1
		[8] tile_id1
		...
		...
		[n] tile_idN
		[n+1] tile_idN

		Obs: N = width * height * numLayers;

		Tile ID comes in the correct sequence, from topLeft to bottomRight order, from the backLayer to topLayer order.	
		
		*/

	unsigned short messageSize = readShortByte(&message, 0);
	int messageType = readIntByte(&message, 2);
	int map_id = readIntByte(&message, 3);
	int width = readIntByte(&message, 4);
	int height = readIntByte(&message, 5);
	int numLayers = readIntByte(&message, 6);

	int tileDataSize = width * height * numLayers * 2;

	// Check sanity
	if (tileDataSize + 7 != messageSize)
	{
		//std::cout << "Incorrect message format. Expected Data Size = " << (tileDataSize-7) << " DataSize calculated: " <<  << std::endl;
	}

	for (int i = 7; i < messageSize; i += 2)
	{
		unsigned short tileId = readShortByte(&message, i);
		this->tileList.push_back(tileId);
	}
}

GC_Net_MapLoadMessage::~GC_Net_MapLoadMessage()
{
}
