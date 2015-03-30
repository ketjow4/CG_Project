#include "Camera.h"

//#define TEST

Camera::Camera()
{
	centerx = 0;
	centery = -0.2;
	centerz = 1;
	eyex = 3;
	eyey = 7;
	eyez = -10;
	STEP_SCALE = 1.0;
	m_up = Vector3f(0,1,0);


	Vector3f HTarget(centerx, 0.0, centerz);
    HTarget.Normalize();
    
    if (HTarget.z >= 0.0f)
    {
        if (HTarget.x >= 0.0f)
        {
            yawAngle = 360.0f - ToDegree(asin(HTarget.z));
        }
        else
        {
           yawAngle = 180.0f + ToDegree(asin(HTarget.z));
        }
    }
    else
    {
        if (HTarget.x >= 0.0f)
        {
            yawAngle = ToDegree(asin(-HTarget.z));
        }
        else
        {
            yawAngle = 90.0f + ToDegree(asin(-HTarget.z));
        }
    }
    
	m_AngleV = -ToDegree(asin(centery));

}

void Camera::UpdateCamera()
{
		const Vector3f Vaxis(0.0f, 1.0f, 0.0f);

    // Rotate the view vector by the horizontal angle around the vertical axis
    Vector3f View(1.0f, 0.0f, 0.0f);
	View.Rotate(yawAngle, Vaxis);
    View.Normalize();

    // Rotate the view vector by the vertical angle around the horizontal axis
    Vector3f Haxis = Vaxis.Cross(View);
    Haxis.Normalize();
	View.Rotate(45, Haxis);
       
	View.Normalize();

	centerx = View.x;
	centery = View.y;
	centerz = View.z;

	m_up = View.Normalize().Cross(Haxis);
    m_up.Normalize();
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
	eyex += (Vector3f(centerx,centery,centerz) * STEP_SCALE).x;
	//eyey += (Vector3f(centerx,centery,centerz) * STEP_SCALE).y;
	eyez += (Vector3f(centerx,centery,centerz) * STEP_SCALE).z;
}

void Camera::MoveBackward(double delta)
{
	eyex -= (Vector3f(centerx,centery,centerz) * STEP_SCALE).x;
	//eyey += (Vector3f(centerx,centery,centerz) * STEP_SCALE).y;
	eyez -= (Vector3f(centerx,centery,centerz) * STEP_SCALE).z;
}

void Camera::MoveLeft(double delta)
{
	Vector3f Left = Vector3f(centerx,centery,centerz).Cross(Vector3f(0,1,0));

	Left.Normalize();
	Left *= STEP_SCALE;
	eyex += Left.x;
	eyey += Left.y;
	eyez += Left.z;
}

void Camera::MoveRight(double delta)
{
	Vector3f Right = Vector3f(0,1,0).Cross(Vector3f(centerx,centery,centerz));

	Right.Normalize();
	Right *= STEP_SCALE;
	eyex += Right.x;
	eyey += Right.y;
	eyez += Right.z;
}

void Camera::Rotate(double angle)
{
	yawAngle += angle;
}