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
	/** Identyfikator wybranej wie¿y */
	int selectedTower;
	/** Identyfikator przycisku najechanego mysz¹ */
	int buttonHover;
	/** Identyfikator akcji do podjêcia */
	int action;

	GameHUD();
	~GameHUD();
	/**
	* Funkcja wyœwietla HUD.
	* @param enemiesLeft pozostali przeciwncy w danej fali
	*/
	void Draw(const int &enemiesLeft);
	/**
	* Funkcja obsu³gu¹ca zdarzenie klikniêcia myszy w menu. Zwraca identyfikator klikniêtego elementu.
	* @param x znormalizowana wspó³rzêdna x kursora wzglêdem okna
	* @param y znormalizowana wspó³rzêdna y kursora wzglêdem okna
	*/
	int CheckWhereMouseClickedAndReact(int x, int y);
	/**
	* Funkcja obsu³gu¹ca zdarzenie przesuniêcia myszy w menu.
	* @param x znormalizowana wspó³rzêdna x kursora wzglêdem okna
	* @param y znormalizowana wspó³rzêdna y kursora wzglêdem okna
	*/
	void CheckMouseMoveAndReact(int x, int y);
	/**
	* Funkcja wyœwietla informacje o pora¿ce.
	*/
	void DrawGameOverInfo();
	/**
	* Funkcja wyœwietla informacje o zwyciêstwie.
	*/
	void DrawYouWonInfo();
	/**
	* Funkcja zwraca identyfikator akcji zmiany widocznoœci HUD.
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

