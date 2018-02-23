#include "GC_Font.h"


GC_Font::GC_Font(std::string id, std::string fontPath, int fontSize)
	: GC_IResource(),  filePath(fontPath), fontSize(fontSize)
{
	this->id = id;
	
	this->readyToLoad = this->isReadyToLoad();
}

GC_Font::~GC_Font()
{

}

bool GC_Font::loadResource()
{
	if (this->isReadyToLoad())
	{
		TTF_Font * ttfFont = TTF_OpenFont(this->filePath.c_str(), this->fontSize);
		if (ttfFont)
		{
			this->font = std::shared_ptr<TTF_Font>(ttfFont, [=](TTF_Font*font) {
				std::cout << "Destroying Font: " << this->getId();
				TTF_CloseFont(font);
				std::cout << " ...Done. " << std::endl;
			
			});
			return true;
		} 
		else
		{
			std::cout << "Error loading font [" << this->filePath << "] "<< TTF_GetError() << std::endl;
			return false;
		}
	} 
	else
	{
		// throw exception?
		return false;
	}
}

TTF_Font * GC_Font::getFont()
{
	return this->font.get();
}

bool GC_Font::isReadyToLoad()
{
	return !this->filePath.empty() && this->fontSize > 0 && !this->id.empty();
}
