#include "Enemy.h"

const float Enemy::EffectIntensity[2] = { 0.f, 0.4f };
const Vector4f Enemy::EffectColor[2] = { Vector4f(1.f, 1.f, 1.f, 1.f), Vector4f(0.2f, 1.f, 0.f, 1.f) };

Enemy::Enemy()
	: pathIndex(0), HP(100), Attack(1), effectId(0)
{
	poison.duration = 0;
	poison.degenFreq = 10;
}

Enemy::~Enemy()
{}

void Enemy::LoadModel(int id)
{
	model = (Mesh*)ModelsContainer::Get(id);
}

void Enemy::UpdatePosition(Pipeline *p, Camera* cam)
{
	simpleModel->Enable();

	if (poison.duration > 0)
	{
		if (--poison.duration % poison.degenFreq == 0)
			--HP;
		effectId = 1;
	}
	else
	{
		effectId = 0;
	}

	if(HP <= 0)			//in future delete enemy in this case
		return ;		

	p->Scale(0.3f, 0.3f, 0.3f);
	float x = path->pathPoints[pathIndex].first;
	float z = path->pathPoints[pathIndex].second;
	float y = terrain->GetTerrainHeight(x, z);
	rotation = path->GetRotation(Vector3f(x,y,z),pathIndex);
	p->Rotate(rotation);

	p->WorldPos(x,y+1.0,z);
	position = Vector3f(x, y + 1, z);

	simpleModel->SetWVP(p->GetWVPTrans());
	simpleModel->SetWV(p->GetWVTrans());
	simpleModel->SetWorldMatrix(p->GetWorldTrans());
	simpleModel->SetColorEffect(EffectColor[effectId]);
	simpleModel->SetColorEffectIntensity(EffectIntensity[effectId]);
	p->SetCamera(Vector3f(-100.0, 300.0, -100.0f), Vector3f(0.2f, -1.0f, 0.1f), Vector3f(0.0f, 1.0f, 0.0f));
	simpleModel->SetLightWVP(p->GetWVPTrans());

	model->Render();

	p->SetCamera(Vector3f(cam->eyex, cam->eyey, cam->eyez), Vector3f(cam->centerx, cam->centery, cam->centerz), cam->m_up);
	simpleModel->SetColorEffectIntensity(0.f);

	if (++pathIndex >= path->pathPoints.size() - 1)				//object arrived at end point 
	{
		HP = 0;
		pathIndex = 0;
		Player::getPlayer().LooseLive(Attack);
	}
}


const Vector3f& Enemy::GetPosition() const
{
	return position;
}

const Vector3f& Enemy::GetRotation() const
{
	return rotation;
}

const int& Enemy::GetPathIndex() const
{
	return pathIndex;
}

Vector3f Enemy::GetFuturePosition(int steps) const
{
	int futurePathIndex = min(pathIndex + steps, (int)path->pathPoints.size() - 1);
	float x = path->pathPoints[futurePathIndex].first;
	float z = path->pathPoints[futurePathIndex].second;
	float y = terrain->GetTerrainHeight(x, z)  + 10;
	return Vector3f(x, y, z);
}

void Enemy::SetSimpleModel(SimpleModelTechnique* simpleModel)
{
	this->simpleModel = simpleModel;
}

void Enemy::SetTerrain(Terrain* terrain)
{
	this->terrain = terrain;
}
void Enemy::SetPath(Path* path)
{
	this->path = path;
}