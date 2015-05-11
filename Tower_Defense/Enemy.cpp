#include "Enemy.h"

Enemy::Enemy()
{
	pathIndex = 0;
	HP = 150;
	Attack = 1;			//to use later when there will be player class
}

Enemy::~Enemy()
{
}

void Enemy::LoadModel(string filename)
{
	model.LoadMesh(filename);
}


void Enemy::UpdatePosition(Pipeline *p)
{
	light->Enable();

	if(HP <= 0)			//in future delete enemy in this case
	{
		this->~Enemy();
		return ;		
	}

	p->Scale(0.1f, 0.1f, 0.1f);
	float x = path->pathPoints[pathIndex].first;
	float z = path->pathPoints[pathIndex].second;
	float y = terrain->GetTerrainHeight(x, z);
	p->Rotate(path->GetRotation(Vector3f(x,y,z),pathIndex));

	p->WorldPos(x,y+1.0,z);
	position = Vector3f(x, y + 1, z);

	light->SetWVP(p->GetWVPTrans());
	model.Render();

	if (++pathIndex >= path->pathPoints.size() - 1)				//object arrived at end point		-- for now return to start 
		pathIndex = 0;
}


Vector3f Enemy::GetPosition()
{
	return position;
}