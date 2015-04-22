#include "Tower.h"


Tower::Tower()
{
}

Tower::~Tower()
{
}

void Tower::Shoot()
{
	//create missile
	//shot at target
	//trace targer
	//if missed destroy missile
}



void Tower::SetPosition(Vector3f position)
{
	this->WorldPosition = position;
}

void Tower::LoadModel(string filename)
{
	this->Model3D.LoadMesh(filename);
}


void Tower::LoadMissile(string filename)
{
	this->LoadMissile.LoadMesh(filename);
}