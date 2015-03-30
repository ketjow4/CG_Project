#ifndef CAMERA_H
#define CAMERA_H

#include <stdlib.h>
#include <glut.h>

#include <glm/glm.hpp>					//biblioteka pomocnicza zawierajaca operacje na macierzach i wektorach
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "math_3d.h"

class Camera
{
public:
	// wpó³rzêdne po³o¿enia obserwatora
	GLdouble eyex;
	GLdouble eyey;
	GLdouble eyez;


	// wspó³rzêdne punktu w którego kierunku jest zwrócony obserwator,
	GLdouble centerx;
	GLdouble centery;
	GLdouble centerz;

	GLfloat yawAngle;

	double STEP_SCALE;

	Vector3f m_up;
	float m_AngleV;

public:

	Camera();

	void UpdateCamera();

	void SetRotation(double angle);

	void SetPosition(double x, double y, double z);

	void SetCenterPoint(double x, double y, double z);

	void MoveForward(double delta);

	void MoveBackward(double delta);

	void MoveLeft(double delta);

	void MoveRight(double delta);

	void Rotate(double angle);
};

#endif