#include "pipeline.h"

const Matrix4f& Pipeline::GetVPTrans()
{
    Matrix4f CameraTranslationTrans, CameraRotateTrans, PersProjTrans;

    CameraTranslationTrans.InitTranslationTransform(-m_camera.Pos.x, -m_camera.Pos.y, -m_camera.Pos.z);
    CameraRotateTrans.InitCameraTransform(m_camera.Target, m_camera.Up);
    PersProjTrans.InitPersProjTransform(m_persProjInfo);
    
    m_VPtransformation = PersProjTrans * CameraRotateTrans  * CameraTranslationTrans ;
    return m_VPtransformation;
}

const Matrix4f& Pipeline::GetWorldTrans()
{
    Matrix4f ScaleTrans, RotateTrans, TranslationTrans;

    ScaleTrans.InitScaleTransform(m_scale.x, m_scale.y, m_scale.z);
    RotateTrans.InitRotateTransform(m_rotateInfo.x, m_rotateInfo.y, m_rotateInfo.z);
    TranslationTrans.InitTranslationTransform(m_worldPos.x, m_worldPos.y, m_worldPos.z);

    m_Wtransformation = TranslationTrans * RotateTrans * ScaleTrans;
    return m_Wtransformation;
}

const Matrix4f& Pipeline::GetWVPTrans()
{
    GetWorldTrans();
    GetVPTrans();

    m_WVPtransformation = m_VPtransformation * m_Wtransformation;
    return m_WVPtransformation;
}

const Matrix4f& Pipeline::GetWVTrans()
{
	GetWorldTrans();
	
	Matrix4f CameraTranslationTrans, CameraRotateTrans;

	CameraTranslationTrans.InitTranslationTransform(-m_camera.Pos.x, -m_camera.Pos.y, -m_camera.Pos.z);
	CameraRotateTrans.InitCameraTransform(m_camera.Target, m_camera.Up);
	
	m_WVtransformation = CameraRotateTrans * CameraTranslationTrans * m_Wtransformation;
	return m_WVtransformation;
}


const Matrix4f& Pipeline::GetWPTrans()
{
	Matrix4f PersProjTrans;

	GetWorldTrans();
	PersProjTrans.InitPersProjTransform(m_persProjInfo);

	m_WPtransformation = PersProjTrans * m_Wtransformation;
	return m_WPtransformation;
}


//const Matrix4f& Pipeline::GetOrthographicTrans()
//{
//	double screenWidth = 640.0;
//	double screenHeight = 480.0;
//	Matrix4f mat = Matrix4f(2.0 / (screenWidth - 0.0), 0, 0, -(screenWidth + 0.0) / (screenWidth - 0.0), 0, 2.0 / (screenHeight - 0.0), 0, -(screenHeight + 0) / (screenHeight - 0), 0, 0, -2.0 / (1.0 + 1.0), -(1.0 - 1.0) / (1.0 + 1.0), 0, 0, 0, 1);
//
//	return m_WPtransformation = mat;
//}


