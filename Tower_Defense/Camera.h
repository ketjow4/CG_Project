#pragma once

#include <stdlib.h>
#include <glut.h>

#include <glm/glm.hpp>					//biblioteka pomocnicza zawierajaca operacje na macierzach i wektorach
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "math_3d.h"

class Camera
{
public:
	/** Wp�rz�dne po�o�enia obserwatora */
	GLdouble eyex, eyey, eyez;
	/** Znormalizowany wektor kierunku, w kt�rym zwr�cona jest kamera */
	GLdouble centerx,centery,centerz;
	GLfloat yawAngle;
	double STEP_SCALE;
	Vector3f m_up;
	float m_AngleV;

	Camera();
	/**
	* Funkcja aktualizuje kamer�.
	*/
	void UpdateCamera();
	/**
	* Funkcja ustawia k�t obrotu kamery.
	*/
	void SetRotation(double angle);
	/**
	* Funkcja ustawia pozycj� kamery.
	* @param x wsp�rzedna x kamery
	* @param y wsp�rzedna y kamery
	* @param z wsp�rzedna z kamery
	*/
	void SetPosition(double x, double y, double z);
	/**
	* Funkcja kierunek, w kt�rym zwr�cona jest kamera.
	* @param x wsp�rzedna x wektora kierunku
	* @param y wsp�rzedna y wektora kierunku
	* @param z wsp�rzedna z wektora kierunku
	*/
	void SetCenterPoint(double x, double y, double z);
	/**
	* Przesuwa kamer� do przodu.
	* @param delta przesuni�cie
	*/
	void MoveForward(double delta);
	/**
	* Przesuwa kamer� do ty�u.
	* @param delta przesuni�cie
	*/
	void MoveBackward(double delta);
	/**
	* Przesuwa kamer� w lewo.
	* @param delta przesuni�cie
	*/
	void MoveLeft(double delta);
	/**
	* Przesuwa kamer� w prawo.
	* @param delta przesuni�cie
	*/
	void MoveRight(double delta);
	/**
	* Obraca kamer�.
	* @param delta zmiana k�ta
	*/
	void Rotate(double angle);
};
