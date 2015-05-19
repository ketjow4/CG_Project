#include "PathsContainer.h"

map<int, Path*> PathsContainer::paths;

PathsContainer::PathsContainer()
{}


PathsContainer::~PathsContainer()
{
	FreeResources();
}

void PathsContainer::FreeResources()
{
	while (!paths.empty())
	{
		map<int, Path*>::iterator it = paths.begin();
		delete it->second;
		paths.erase(it);
	}
}

void PathsContainer::LoadPath(int key, const string &pathBmp)
{
	if (paths.find(key) == paths.end())
	{
		Path* path = new Path();
		path->Init(pathBmp);
		paths.insert(make_pair(key, path));
	}
}

Path* PathsContainer::Get(int key)
{
	map<int, Path*>::iterator it = paths.find(key);
	if (it == paths.end())
		return 0;
	return it->second;
}