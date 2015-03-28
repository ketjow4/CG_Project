#include "Camera.h"

//#define TEST

Camera::Camera()
{
//#ifndef TEST
	//centerx = 0;
	//centery = 0;
	//centerz = 0;
	//eyex = 0;
	//eyey = 50;
	//eyez = 0;
	//yawAngle = 0;
//#elif
	centerx = 0;
	centery = -0.2;
	centerz = 1;
	eyex = 3;
	eyey = 7;
	eyez = -10;
	//yawAngle = 0;
//#endif
	/*centerx = 0;
	centery = -1;
	centerz = 1;
	eyex = 0;
	eyey = 15;
	eyez = 0;
	yawAngle = 0;*/

}

void Camera::UpdateCamera()
{
	//eyex = sin(glm::radians(yawAngle)) * 5;		
	//eyez = cos(glm::radians(yawAngle)) * 5;
	//gluLookAt( eyex + centerx, eyey, eyez + centerz, centerx, centery, centerz, 0, 1, 0 );	//prosta kamera która obraca siê  i przesuwa w jednej p³aszczyŸnie (xz) 
#ifndef TEST
	//dla moich testow
	//eyex = sin(glm::radians(yawAngle)) * 100;		
	//eyez = cos(glm::radians(yawAngle)) * 100;
	//gluLookAt( eyex + centerx, eyey, eyez + centerz, centerx, centery, centerz, 0, 1, 0 );	//prosta kamera która obraca siê  i przesuwa w jednej p³aszczyŸnie (xz) 
#endif	
	//eyex = yawAngle;
	//eyez = yawAngle;
}

void Camera::SetRotation(double angle)
{
	yawAngle = angle;
}

void Camera::SetPosition(double x, double y, double z)
{
	eyex = x;
	eyey = y;
	eyez = z;
}

void Camera::SetCenterPoint(double x, double y, double z)
{
	centerx = x;
	centery = y;
	centerz = z;
}

void Camera::MoveForward(double delta)
{
	eyez -= delta * cos(glm::radians(yawAngle));
	eyex -= delta * sin(glm::radians(yawAngle));
}

void Camera::MoveBackward(double delta)
{
	eyez += delta * cos(glm::radians(yawAngle));
	eyex += delta * sin(glm::radians(yawAngle));
}

void Camera::MoveLeft(double delta)
{
	eyex -= delta * cos(glm::radians(yawAngle));
	eyez += delta * sin(glm::radians(yawAngle));
}

void Camera::MoveRight(double delta)
{
	eyex += delta * cos(glm::radians(yawAngle));
	eyez -= delta * sin(glm::radians(yawAngle));
}

void Camera::Rotate(double angle)
{
	yawAngle += angle;
}