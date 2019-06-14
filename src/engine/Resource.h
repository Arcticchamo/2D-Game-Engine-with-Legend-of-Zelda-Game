#pragma once
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource
{
protected:
	std::string filePath;
public:
	std::string GetFilePath() { return filePath; }

	virtual ~Resource() {}
};
#endif