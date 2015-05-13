#pragma once
#include "Model.h"

#include <map>

static class ModelsContainer
{
public:
	static void Load(int key, const string &filename);
	static void Save(int key, Mesh *mesh);
	static Mesh* Get(int key);
	static void FreeResources();
private:
	static map<int, Mesh*> models;

	ModelsContainer();
	~ModelsContainer();
};
