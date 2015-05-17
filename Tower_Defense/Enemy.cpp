#include "Enemy.h"

const float Enemy::EffectIntensity[2] = { 0.f, 0.4f };
const Vector4f Enemy::EffectColor[2] = { Vector4f(1.f, 1.f, 1.f, 1.f), Vector4f(0.2f, 1.f, 0.f, 1.f) };

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

	effectId = HP < 50 ? 1 : 0;		// TMP effect change

	light->SetWVP(p->GetWVPTrans());
	light->SetColorEffect(EffectColor[effectId]);
	light->SetColorEffectIntensity(EffectIntensity[effectId]);
	model->Render();
	light->SetColorEffectIntensity(0.f);

	if (++pathIndex >= path->pathPoints.size() - 1)				//object arrived at end point		-- for now return to start 
	{
		pathIndex = 0;
		Player::getPlayer().LooseLive(Attack);
	}
}


const Vector3f& Enemy::GetPosition() const
{
	return position;
}

Vector3f Enemy::GetFuturePosition(int steps) const
{
	int futurePathIndex = min(pathIndex + steps, (int)path->pathPoints.size() - 1);
	float x = path->pathPoints[futurePathIndex].first;
	float z = path->pathPoints[futurePathIndex].second;
	float y = terrain->GetTerrainHeight(x, z);
	return Vector3f(x, y, z);
}