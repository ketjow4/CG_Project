#include "Camera.h"

Camera::Camera()
{
	centerx = 0;
	centery = 0;
	centerz = 0;
	eyex = 0;
	eyey = 3;
	eyez = 0;
	yawAngle = 0;
}

void Camera::UpdateCamera()
{
	eyex = sin(glm::radians(yawAngle)) * 5;		
	eyez = cos(glm::radians(yawAngle)) * 5;
	gluLookAt( eyex + centerx, eyey, eyez + centerz, centerx, centery, centerz, 0, 1, 0 );	//prosta kamera która obraca siê  i przesuwa w jednej p³aszczyŸnie (xz) 
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
	centerz -= delta * cos(glm::radians(yawAngle));
	centerx -= delta * sin(glm::radians(yawAngle));
}

void Camera::MoveBackward(double delta)
{
	centerz += delta * cos(glm::radians(yawAngle));
	centerx += delta * sin(glm::radians(yawAngle));
}

void Camera::MoveLeft(double delta)
{
	centerx -= delta * cos(glm::radians(yawAngle));
	centerz += delta * sin(glm::radians(yawAngle));
}

void Camera::MoveRight(double delta)
{
	centerx += delta * cos(glm::radians(yawAngle));
	centerz -= delta * sin(glm::radians(yawAngle));
}

void Camera::Rotate(double angle)
{
	yawAngle += angle;
}