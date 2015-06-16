#pragma once
#include "math_3d.h"
#include <vector>

class Mouse
{
public:
	/** Pozycja myszki wzgl�dem interfejsu 2d */
	Vector2i normalizedPos2d;
	/** Pozycja myszki w oknie programu */
	Vector2i pos2d;
	/** Pozycja myszki w �wiecie gry */
	Vector3f pos3d;
	bool leftClick;
	bool rightClick;

	Mouse();
	~Mouse();

	/**
	* Funckja ustawiaj�ca w�a�ciwo�ci myszki na podstawie zdarzenie klikni�cia lewego przycisku.
	* @param x wsp�rz�dna x wzgl�dem okna programu
	* @param y wsp�rz�dna y wzgl�dem okna programu
	*/
	void MouseLeftClick(int x, int y);
	/**
	* Funckja ustawiaj�ca w�a�ciwo�ci myszki na podstawie zdarzenie klikni�cia prawego przycisku.
	* @param x wsp�rz�dna x wzgl�dem okna programu
	* @param y wsp�rz�dna y wzgl�dem okna programu
	*/
	void MouseRightClick(int x, int y);
	/**
	* Funckja ustawiaj�ca w�a�ciwo�ci myszki na podstawie zdarzenie ruchu kursora.
	* @param x wsp�rz�dna x wzgl�dem okna programu
	* @param y wsp�rz�dna y wzgl�dem okna programu
	*/
	void MouseMove(int x, int y);
	/**
	* Funckja ustawiaj�ca pozycje myszki w �wiecie gry.
	* @param x wsp�rz�dna x w �wiecie gry
	* @param y wsp�rz�dna y w �wiecie gry
	* @param z wsp�rz�dna z w �wiecie gry
	*/
	void SetPos3d(float x, float y, float z);
	/**
	* Funckja nadpisuj�ce wsp�rz�dne okna pami�tane przez myszk�. Nale�y wywo�a� przy ka�dej zmianie rozmiaru okna.
	* @param w nowa szeroko�� okna
	* @param h nowa wysoko�� okna
	*/
	void SetWindowSize(int w, int h);
	/**
	* Funkcja zwracaj�ca odleg�o�� kursora w �wiecie gry od najbli�szego z podanych punkt�w. Pomija wsp�rzedn� y.
	* @param pointsXZ punkty (x,z), z kt�rymi por�wnywana jest pozycja kursora
	* @param closestXZ najbli�szy kursora punkt wyznaczany w funkcji
	*/
	float DistToClosest(const vector <pair<float, float>> &pointsXZ, pair<float, float> &closestXZ);
private:
	const static int DefaultWinW;
	const static int DefaultWinH;
	int winW, winH;
	
	float DistToPointXZ(const pair<float, float> &p);
};
