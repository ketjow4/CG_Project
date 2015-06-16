#pragma once
#include "math_3d.h"
#include <vector>

class Mouse
{
public:
	/** Pozycja myszki wzglêdem interfejsu 2d */
	Vector2i normalizedPos2d;
	/** Pozycja myszki w oknie programu */
	Vector2i pos2d;
	/** Pozycja myszki w œwiecie gry */
	Vector3f pos3d;
	bool leftClick;
	bool rightClick;

	Mouse();
	~Mouse();

	/**
	* Funckja ustawiaj¹ca w³aœciwoœci myszki na podstawie zdarzenie klikniêcia lewego przycisku.
	* @param x wspó³rzêdna x wzglêdem okna programu
	* @param y wspó³rzêdna y wzglêdem okna programu
	*/
	void MouseLeftClick(int x, int y);
	/**
	* Funckja ustawiaj¹ca w³aœciwoœci myszki na podstawie zdarzenie klikniêcia prawego przycisku.
	* @param x wspó³rzêdna x wzglêdem okna programu
	* @param y wspó³rzêdna y wzglêdem okna programu
	*/
	void MouseRightClick(int x, int y);
	/**
	* Funckja ustawiaj¹ca w³aœciwoœci myszki na podstawie zdarzenie ruchu kursora.
	* @param x wspó³rzêdna x wzglêdem okna programu
	* @param y wspó³rzêdna y wzglêdem okna programu
	*/
	void MouseMove(int x, int y);
	/**
	* Funckja ustawiaj¹ca pozycje myszki w œwiecie gry.
	* @param x wspó³rzêdna x w œwiecie gry
	* @param y wspó³rzêdna y w œwiecie gry
	* @param z wspó³rzêdna z w œwiecie gry
	*/
	void SetPos3d(float x, float y, float z);
	/**
	* Funckja nadpisuj¹ce wspó³rzêdne okna pamiêtane przez myszkê. Nale¿y wywo³aæ przy ka¿dej zmianie rozmiaru okna.
	* @param w nowa szerokoœæ okna
	* @param h nowa wysokoœæ okna
	*/
	void SetWindowSize(int w, int h);
	/**
	* Funkcja zwracaj¹ca odleg³oœæ kursora w œwiecie gry od najbli¿szego z podanych punktów. Pomija wspó³rzedn¹ y.
	* @param pointsXZ punkty (x,z), z którymi porównywana jest pozycja kursora
	* @param closestXZ najbli¿szy kursora punkt wyznaczany w funkcji
	*/
	float DistToClosest(const vector <pair<float, float>> &pointsXZ, pair<float, float> &closestXZ);
private:
	const static int DefaultWinW;
	const static int DefaultWinH;
	int winW, winH;
	
	float DistToPointXZ(const pair<float, float> &p);
};
