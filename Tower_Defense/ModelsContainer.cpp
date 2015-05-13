#include "ModelsContainer.h"

map<int, Mesh*> ModelsContainer::models;

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
		map<int, Mesh*>::iterator it = models.begin();
		delete it->second;
		models.erase(it);
	}
}

void ModelsContainer::Load(int key, const string &filename)
{
	if (models.find(key) == models.end())
	{
		Mesh *mesh = new Mesh();
		mesh->LoadMesh(filename);
		models.insert(make_pair(key, mesh));
	}
}

void ModelsContainer::Save(int key, Mesh *mesh)
{
	if (models.find(key) == models.end())
		models.insert(make_pair(key, mesh));
}

Mesh* ModelsContainer::Get(int key)
{
	map<int, Mesh*>::iterator it = models.find(key);
	if (it == models.end())
		return 0;
	return it->second;
}