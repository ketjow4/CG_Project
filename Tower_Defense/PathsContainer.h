#pragma once
#include "Path.h"

#include <map>

class PathsContainer
{
public:
	static void LoadPath(int key, const string &pathBmp);
	static Path* Get(int key);
	static void FreeResources();
private:
	static map<int, Path*> paths;

	PathsContainer();
	~PathsContainer();
};

