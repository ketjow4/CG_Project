#ifndef CAMERA_H
#define CAMERA_H

#include <stdlib.h>
#include <glut.h>

#include <glm/glm.hpp>					//biblioteka pomocnicza zawierajaca operacje na macierzach i wektorach
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Camera
{
public:
	// wp�rz�dne po�o�enia obserwatora
	GLdouble eyex;
	GLdouble eyey;
	GLdouble eyez;


	// wsp�rz�dne punktu w kt�rego kierunku jest zwr�cony obserwator,
	GLdouble centerx;
	GLdouble centery;
	GLdouble centerz;

	GLfloat yawAngle;

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