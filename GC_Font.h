#pragma once
#include "GC_IResource.h"
#include <SDL_ttf.h>
class GC_Font :
	public GC_IResource
{
private:
	std::shared_ptr<TTF_Font> font;
	std::string filePath;
	int fontSize;
	bool readyToLoad;
protected:
	bool isReadyToLoad();
public:
	GC_Font(std::string id, std::string fontPath, int fontSize);
	virtual ~GC_Font();
	
	bool loadResource();
	TTF_Font * getFont();
	
};

