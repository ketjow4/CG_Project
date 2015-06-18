#pragma once
#include <string>
#include "Text.h"
#include "texture.h"
#include "GameConstsDefinitions.h"
#include "Player.h"

#include "Drawing2D.h"

class GameHUD
{
public:
	/** Identyfikator wybranej wie�y */
	int selectedTower;
	/** Identyfikator przycisku najechanego mysz� */
	int buttonHover;
	/** Identyfikator akcji do podj�cia */
	int action;

	GameHUD();
	~GameHUD();
	/**
	* Funkcja wy�wietla HUD.
	* @param enemiesLeft pozostali przeciwncy w danej fali
	*/
	void Draw(const int &enemiesLeft);
	/**
	* Funkcja obsu�gu�ca zdarzenie klikni�cia myszy w menu. Zwraca identyfikator klikni�tego elementu.
	* @param x znormalizowana wsp�rz�dna x kursora wzgl�dem okna
	* @param y znormalizowana wsp�rz�dna y kursora wzgl�dem okna
	*/
	int CheckWhereMouseClickedAndReact(int x, int y);
	/**
	* Funkcja obsu�gu�ca zdarzenie przesuni�cia myszy w menu.
	* @param x znormalizowana wsp�rz�dna x kursora wzgl�dem okna
	* @param y znormalizowana wsp�rz�dna y kursora wzgl�dem okna
	*/
	void CheckMouseMoveAndReact(int x, int y);
	/**
	* Funkcja wy�wietla informacje o pora�ce.
	*/
	void DrawGameOverInfo();
	/**
	* Funkcja wy�wietla informacje o zwyci�stwie.
	*/
	void DrawYouWonInfo();
	/**
	* Funkcja zwraca identyfikator akcji zmiany widoczno�ci HUD.
	*/
	int  ShowHide() const;
private:

	const static int FirstTowerX = 0;
	const static int FirstTowerY = 0;
	const static int SecondTowerX = FirstTowerX + 43;
	const static int SecondTowerY = FirstTowerY;

	const static int FirstTowerMouseX = 0;
	const static int FirstTowerMouseY = 480;
	const static int SecondTowerMouseX = FirstTowerMouseX + 43;
	const static int SecondTowerMouseY = FirstTowerMouseY;

	int mouseHover;
	Drawing2D draw2d;

	Text *text;
	Text *text14;

	Texture *BackgroundImg;
	Texture *FirstTowerImg;
	Texture *FirstTowerImgHover;
	Texture *SecondTowerImg;
	Texture *SecondTowerImgHover;
	Texture *FirstTowerImgClick;
	Texture *SecondTowerImgClick;
	Texture *GameOver;
	Texture *YouWon;

	// The text controls of the different entries.
	std::string NewGameText;
	std::string ExitText;
	std::string ResumeGameText;

	void DrawGameInfo(const int &enemiesLeft);
	void DrawButtons();
	void DrawTextureButtons();

};

