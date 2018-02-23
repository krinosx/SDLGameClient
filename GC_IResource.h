#pragma once
#include <memory>
#include <string>
#include <iostream>
class GC_IResource
{
protected:
	std::string id;
	virtual bool isReadyToLoad() = 0;

public:
	virtual ~GC_IResource() {};
	
	void setId(std::string id);
	std::string getId();

};

