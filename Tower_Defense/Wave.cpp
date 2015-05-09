#include "Wave.h"


Wave::Wave()
{
}

Wave::~Wave()
{
}

Wave::Wave(vector<Enemy*>* list, Pipeline *p)
{
	enemyList = list;
	this->p = p;
}



void Wave::UpdatePosition()
{
	for(int i = 0; i < enemyList->size(); i++)
	{
		enemyList->at(i)->UpdatePosition(p);
	}

}

void Wave::ClearDead()
{
	//vector<Enemy> newList;
	//for(int i = 0; i < enemyList.size(); i++)
	//{
	//	if(&enemyList[i] != NULL)					//check this
	//		newList.push_back(enemyList[i]);
	//}
	//enemyList.clear();
	//enemyList = newList;
}