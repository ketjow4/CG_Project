#pragma once
#include <string>
using namespace std;

class Renderable
{
public:
	virtual ~Renderable(){};
	virtual void Render() = 0;
	virtual bool LoadMesh(const string &filename) = 0;
};

