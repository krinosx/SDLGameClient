#include "GC_Scene.h"

GC_Scene::GC_Scene(std::string id)
{
	this->id = id;
}

GC_Scene::~GC_Scene()
{
}

std::string GC_Scene::getId()
{
	return this->id;
}
