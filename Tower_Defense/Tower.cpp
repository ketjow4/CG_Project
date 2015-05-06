#include "Tower.h"


Tower::Tower()
{
	//this->missileLife = 1000; //wartoœæ w milisekundach
}


Tower::Tower(BasicLightingTechnique* light, SkinningTechnique* m_pEffect)
{
	this->light = light;
	this->m_pEffect = m_pEffect;
	missilePos =  Vector3f(100,55,100);
	towerPos = missilePos;
	Range = 250;
	missileLife = 0;
}


Tower::~Tower()
{
}


void Tower::Shoot(Pipeline * p, float x, float y, float z)
{
	//get vhicle x,y,z

	static float v = 0;
	v += 0.005;
	if(v > 1)
		v = 0;
	float x_dist = x - missilePos.x;
	float y_dist = y -  missilePos.y;
	float z_dist = z -  missilePos.z;

	distance_to_target =  sqrt(pow(towerPos.x - x,2) + pow(towerPos.z - z, 2));

	if( distance_to_target > Range)
	{
		v = 0;
	}


	p->WorldPos(v*x_dist+missilePos.x,v*y_dist+missilePos.y,v*z_dist+missilePos.z);
	p->Scale(5,5,5);
	p->Rotate(0,0,0);
	light->SetWVP(p->GetWVPTrans());
	missileLife += 30;
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



long long m_startTime;



float GetRunningTime()
{
 float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)m_startTime) / 1000.0f;
    return RunningTime;
}


void Tower::CalcAnimation()
{
	


	m_pEffect->Enable();
	 
	vector<Matrix4f> Transforms;
               
    float RunningTime = GetRunningTime();

	if( distance_to_target > Range)			//no animation playing when enemy is out of range
	{
		RunningTime = 0.1;
	}

	Model3D.BoneTransform(RunningTime, Transforms);
        
        for (uint i = 0 ; i < Transforms.size() ; i++) {
            m_pEffect->SetBoneTransform(i, Transforms[i]);
        }

}

void Tower::Render()
{
	this->Model3D.Render();
	if(missileLife < 10000)
	{
		this->Missile.Render();
	}
	else
	{
		missileLife = 0;
	}
}