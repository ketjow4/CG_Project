#include "Tower.h"


Tower::Tower()
{
	this->missileLife = 1000; //wartoœæ w milisekundach
}

Tower::~Tower()
{
}


void Tower::Shoot()
{
	//create missile
	//shot at target
	//trace target
	//if missed destroy missile
}


void Tower::LoadModel(string filename)
{
	this->Model3D.LoadMesh(filename);
}


void Tower::LoadMissile(string filename)
{
	//this->LoadMissile.LoadMesh(filename);
	this->Missile.LoadMesh(filename);
	missilePos =  Vector3f(100,55,100);
}

void Tower::Render()
{
	//this->Model3D.Render();
	if(missileLife < 10000)
	{
		this->Missile.Render();
	}
	else
	{
		missileLife = 0;
	}
}