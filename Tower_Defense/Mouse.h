#pragma once
#include "math_3d.h"
#include <vector>

class Mouse
{
public:
	Vector2i pos2d;
	Vector3f pos3d;
	bool leftClick;
	bool rightClick;

	Mouse();
	~Mouse();

	void MouseLeftClick(int x, int y);
	void MouseRightClick(int x, int y);
	void MouseMove(int x, int y);
	void SetPos3d(float x, float y, float z);
	void SetWindowSize(int w, int h);

	float DistToClosest(const vector <pair<float, float>> &pointsXZ, pair<float, float> &closestXZ);
private:
	int winW, winH;
	
	float DistToPointXZ(const pair<float, float> &p);
};