#include "Enemy.h"

Enemy::Enemy()
	: pathIndex(0), HP(100), Attack(1)
{}

Enemy::~Enemy()
{}

void Enemy::LoadModel(int id)
{
	model = (Mesh*)ModelsContainer::Get(id);
}

void Enemy::UpdatePosition(Pipeline *p)
{
	light->Enable();

	if(HP <= 0)			//in future delete enemy in this case
		return ;		

	p->Scale(0.3f, 0.3f, 0.3f);
	float x = path->pathPoints[pathIndex].first;
	float z = path->pathPoints[pathIndex].second;
	float y = terrain->GetTerrainHeight(x, z);
	p->Rotate(path->GetRotation(Vector3f(x,y,z),pathIndex));

	p->WorldPos(x,y+1.0,z);
	position = Vector3f(x, y + 1, z);

	light->SetWVP(p->GetWVPTrans());
	model->Render();

	if (++pathIndex >= path->pathPoints.size() - 1)				//object arrived at end point		-- for now return to start 
	{
		pathIndex = 0;
		Player::getPlayer().LooseLive(Attack);
	}
}


Vector3f Enemy::GetPosition()
{
	return position;
}

Vector3f Enemy::GetFuturePosition(int steps)
{
	int futurePathIndex = min(pathIndex + steps, (int)path->pathPoints.size() - 1);
	float x = path->pathPoints[futurePathIndex].first;
	float z = path->pathPoints[futurePathIndex].second;
	float y = terrain->GetTerrainHeight(x, z);
	return Vector3f(x, y, z);
}