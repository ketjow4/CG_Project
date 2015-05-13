#include "Mouse.h"

Mouse::Mouse()
{}

Mouse::~Mouse()
{}

void Mouse::MouseClick(int x, int y)
{
	MouseMove(x, y);
	click = true;
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