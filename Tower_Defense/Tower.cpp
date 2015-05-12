#include "Tower.h"


Tower::Tower()
{
	
}



Tower::Tower(BasicLightingTechnique* light, SkinningTechnique* m_pEffect, Vector3f position, Terrain* ter)
	: light(light), m_pEffect(m_pEffect), towerPos(position), terrain(ter), reloading(0)
{
	towerHeight = 55;			//only good when scale is 5
	towerScale = 5;
	this->LimitTowerPosition();
	towerPos.y = terrain->GetTerrainHeight(towerPos.x, towerPos.z) + towerHeight;
	Range = 250;
}


Tower::~Tower()
{
}


void Tower::Shoot(Enemy* en)
{
	const int reloadTime = 30;
	if (reloading <= 0)
	{
		Vector3f missleDirection = (en->GetPosition() - towerPos).Normalize();
		missiles.push_back(Missile(this->towerPos, missleDirection, 6.f, 200));
		reloading = reloadTime;
	}
}

void Tower::UpdateMissiles(Pipeline * p, list<Enemy> *enemies)
{
	std::list<Missile>::iterator it = missiles.begin();
	while(it != missiles.end())
	{
		UpdateMissile(p, &(*it), enemies);
		if (it->lifetime <= 0)
			it = missiles.erase(it);
		else
			++it;
	}
}

void Tower::Reload()
{
	--reloading;
}

void Tower::UpdateMissile(Pipeline *p, Missile *missile, list<Enemy> *enemies)
{
	list<Enemy>::iterator it = enemies->begin();
	for (; it != enemies->end(); ++it)
		if (missile->Collide(&(*it)))
		{
			it->HP -= 30;
			missile->lifetime = 0;
			return;
		}
	
	/*if (missile->Collide(terrain))
	{
		missile->lifetime = 0;
		return;
	}*/

	missile->UpdateMissile();
	RenderMissile(missile, p);
}

void Tower::RenderMissile(Missile *missile, Pipeline *p)
{
	p->WorldPos(missile->pos);
	p->Scale(1, 1, 1);		//temporary missile scale can be differen than tower scale
	p->Rotate(0, 0, 0);
	light->SetWVP(p->GetWVPTrans());
	MissileMesh.Render();
}


void Tower::LoadModel(string filename)
{
	this->Model3D.LoadMesh(filename);
}


void Tower::LoadMissile(string filename)
{
	this->MissileMesh.LoadMesh(filename);
}


void Tower::CalcAnimation()
{
	m_pEffect->Enable();
	 
	vector<Matrix4f> Transforms;
               
    float RunningTime = Engine::GetRunningTime();

	if( distance_to_target > Range)			//no animation playing when enemy is out of range
	{
		RunningTime = 0.1;
	}

	Model3D.BoneTransform(RunningTime, Transforms);
        
    for (uint i = 0 ; i < Transforms.size() ; i++)
	{
        m_pEffect->SetBoneTransform(i, Transforms[i]);
    }
}

void Tower::Render(Pipeline *p)
{
	p->Scale(towerScale,towerScale,towerScale);
	p->Rotate(0,90,-90);
	p->WorldPos(towerPos);
	m_pEffect->SetWVP(p->GetWVPTrans());
	this->Model3D.Render();
	
}

bool Tower::IsInRange(Vector3f enemyPos)
{
	if( sqrt(pow(towerPos.x - enemyPos.x,2) + pow(towerPos.z - enemyPos.z, 2)) < Range)
	{
		return true;
	}
	else
	{
		distance_to_target = Range + 1;		//hack to get no animation when there is no shooting
		return false;
	}
}

void Tower::LimitTowerPosition()
{
	float maxX = terrain->GetMaxX() -1;		//if the min is zero there is some problem with y simple fast solution
	float minX = terrain->GetMinX() + 1;
	float maxZ = terrain->GetMaxZ() - 1;
	float minZ = terrain->GetMinZ() + 1;

	if(towerPos.x > maxX)
	{
		towerPos.x = maxX;
	}
	else if(towerPos.x < minX)
	{
		towerPos.x = minX;
	}
	if(towerPos.z > maxZ)
	{
		towerPos.z = maxZ;
	}
	else if(towerPos.z < minZ)
	{
		towerPos.z = minZ;
	}
}