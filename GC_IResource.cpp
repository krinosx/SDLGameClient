#include "GC_IResource.h"

void GC_IResource::setId(std::string id)
{
	this->id = id;
}

std::string GC_IResource::getId()
{
	return this->id;
}
