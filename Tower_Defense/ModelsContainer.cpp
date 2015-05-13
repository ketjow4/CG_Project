#include "ModelsContainer.h"

map<int, Renderable*> ModelsContainer::models;

ModelsContainer::ModelsContainer()
{}

ModelsContainer::~ModelsContainer()
{
	FreeResources();
}

void ModelsContainer::FreeResources()
{
	while (!models.empty())
	{
		map<int, Renderable*>::iterator it = models.begin();
		delete it->second;
		models.erase(it);
	}
}

void ModelsContainer::LoadMesh(int key, Renderable *mesh, const string &filename)
{
	if (models.find(key) == models.end())
	{
		mesh->LoadMesh(filename);
		models.insert(make_pair(key, mesh));
	}
	else
	{
		delete mesh;
	}
}

Renderable* ModelsContainer::Get(int key)
{
	map<int, Renderable*>::iterator it = models.find(key);
	if (it == models.end())
		return 0;
	return it->second;
}