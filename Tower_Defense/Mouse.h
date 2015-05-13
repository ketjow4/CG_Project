#pragma once
#include "math_3d.h"

class Mouse
{
public:
	Vector2i pos2d;
	Vector3f pos3d;
	bool click;

	Mouse();
	~Mouse();

	void MouseClick(int x, int y);
	void MouseMove(int x, int y);
	void SetPos3d(float x, float y, float z);
	void SetWindowSize(int w, int h);
private:
	int winW, winH;
};