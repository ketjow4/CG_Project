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
	pos2d.y = y;
}

void Mouse::SetWindowSize(int w, int h)
{
	winW = w;
	winH = h;
}

void Mouse::CalculatePos3d()
{
	//TODO
}