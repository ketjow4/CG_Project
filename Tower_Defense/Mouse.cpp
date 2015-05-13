#include "Mouse.h"

Mouse::Mouse()
{}

Mouse::~Mouse()
{}

void Mouse::MouseLeftClick(int x, int y)
{
	MouseMove(x, y);
	leftClick = true;
}

void Mouse::MouseRightClick(int x, int y)
{
	MouseMove(x, y);
	rightClick = true;
}

void Mouse::MouseMove(int x, int y)
{
	if (pos2d.x == x && pos2d.y == y)
		return;
	pos2d.x = x;
	pos2d.y = winH - y - 1;
}

void Mouse::SetWindowSize(int w, int h)
{
	winW = w;
	winH = h;
}

void Mouse::SetPos3d(float x, float y, float z)
{
	pos3d.x = x;
	pos3d.y = y;
	pos3d.z = z;
}

float Mouse::DistToClosest(const vector <pair<float, float>> &pointsXZ, pair<float, float> &closestXZ)
{
	vector<pair<float, float>>::const_iterator it = pointsXZ.begin();
	float dist = DistToPointXZ(*it);
	closestXZ = *it;
	++it;
	for (float currDist; it != pointsXZ.end(); ++it)
		if ((currDist = DistToPointXZ(*it)) < dist)
			dist = currDist, closestXZ = *it;
	return dist;
}

float Mouse::DistToPointXZ(const pair<float, float> &p)
{
	return sqrt(pow(pos3d.x - p.first, 2.0) + pow(pos3d.z - p.second, 2.0));
}