#include "Tower.h"


Tower::Tower()
{
	
}



Tower::Tower(BasicLightingTechnique* light, SkinningTechnique* m_pEffect, Vector3f position, Terrain* ter)
{
	terrain = ter;
	this->light = light;
	this->m_pEffect = m_pEffect;
	towerHeight = 55;			//only good when scale is 5
	towerScale = 5;
	towerPos = position;
	this->LimitTowerPosition();
	towerPos.y += towerHeight;
	towerPos.y += terrain->GetTerrainHeight(towerPos.x,towerPos.z);
	missilePos = towerPos;
	Range = 250;
	//missileLife = 0;
	
}


Tower::~Tower()
{
}


void Tower::Shoot(Pipeline * p, Enemy* en)
{
	enemy = en;
	static float v = 0;
	v += 0.015;
	if(v > 1)
	{
		v = 0;
		enemy->HP -= 10;
	}
	float x_dist = enemy->GetPosition().x - missilePos.x;
	float y_dist = enemy->GetPosition().y -  missilePos.y;
	float z_dist = enemy->GetPosition().z -  missilePos.z;

	distance_to_target =  sqrt(pow(towerPos.x - enemy->GetPosition().x,2) + pow(towerPos.z - enemy->GetPosition().z, 2));

	if( distance_to_target > Range)
	{
		v = 0;
	}


	p->WorldPos(v*x_dist+missilePos.x,v*y_dist+missilePos.y,v*z_dist+missilePos.z);
	p->Scale(towerScale,towerScale,towerScale);		//temporary missile scale can be differen than tower scale
	p->Rotate(0,0,0);
	light->SetWVP(p->GetWVPTrans());
	//missileLife += 30;
	Missile.Render();
	
}


void Tower::LoadModel(string filename)
{
	this->Model3D.LoadMesh(filename);
}


void Tower::LoadMissile(string filename)
{
	this->Missile.LoadMesh(filename);
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
        
        for (uint i = 0 ; i < Transforms.size() ; i++) {
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
	double maxX = terrain->GetMaxX() -1;		//if the min is zero there is some problem with y simple fast solution
	double minX = terrain->GetMinX() +1;
	double maxZ = terrain->GetMaxZ() -1;
	double minZ = terrain->GetMinZ() +1;

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