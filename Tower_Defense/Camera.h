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
	/** Wpó³rzêdne po³o¿enia obserwatora */
	GLdouble eyex, eyey, eyez;
	/** Znormalizowany wektor kierunku, w którym zwrócona jest kamera */
	GLdouble centerx,centery,centerz;
	GLfloat yawAngle;
	double STEP_SCALE;
	Vector3f m_up;
	float m_AngleV;

	Camera();
	/**
	* Funkcja aktualizuje kamerê.
	*/
	void UpdateCamera();
	/**
	* Funkcja ustawia k¹t obrotu kamery.
	*/
	void SetRotation(double angle);
	/**
	* Funkcja ustawia pozycjê kamery.
	* @param x wspó³rzedna x kamery
	* @param y wspó³rzedna y kamery
	* @param z wspó³rzedna z kamery
	*/
	void SetPosition(double x, double y, double z);
	/**
	* Funkcja kierunek, w którym zwrócona jest kamera.
	* @param x wspó³rzedna x wektora kierunku
	* @param y wspó³rzedna y wektora kierunku
	* @param z wspó³rzedna z wektora kierunku
	*/
	void SetCenterPoint(double x, double y, double z);
	/**
	* Przesuwa kamerê do przodu.
	* @param delta przesuniêcie
	*/
	void MoveForward(double delta);
	/**
	* Przesuwa kamerê do ty³u.
	* @param delta przesuniêcie
	*/
	void MoveBackward(double delta);
	/**
	* Przesuwa kamerê w lewo.
	* @param delta przesuniêcie
	*/
	void MoveLeft(double delta);
	/**
	* Przesuwa kamerê w prawo.
	* @param delta przesuniêcie
	*/
	void MoveRight(double delta);
	/**
	* Obraca kamerê.
	* @param delta zmiana k¹ta
	*/
	void Rotate(double angle);
};
