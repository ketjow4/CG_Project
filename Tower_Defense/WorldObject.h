#ifndef WORLD_OBJ
#define WORLD_OBJ

#include "math_3d.h"
#include "Model.h"

class WorldObject
{
public:

	Vector3f WorldPosition;

	void SetPosition(Vector3f position)
	{
	this->WorldPosition = position;
	}
}


#endif