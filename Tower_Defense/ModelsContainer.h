#pragma once
#include "Renderable.h"
#include "Model.h"

#include <map>

static class ModelsContainer
{
public:
	static void LoadMesh(int key, Renderable *mesh, const string &filename);
	static Renderable* Get(int key);
	static void FreeResources();
private:
	static map<int, Renderable*> models;

	ModelsContainer();
	~ModelsContainer();
};
