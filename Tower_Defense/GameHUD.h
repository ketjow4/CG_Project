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
	GameHUD();
	~GameHUD();

	void Draw(const int &enemiesLeft);
	int  CheckWhereMouseClickedAndReact(int x, int y);
	void CheckMouseMoveAndReact(int x, int y);
	void DrawGameOverInfo();
	void DrawYouWonInfo();
	int  ShowHide();

	int selectedTower;
	int buttonHover;
	int action;

private:

	const int FirstTowerX = 0;
	const int FirstTowerY = 0;
	const int SecondTowerX = FirstTowerX + 43;
	const int SecondTowerY = FirstTowerY;

	const int FirstTowerMouseX = 0;
	const int FirstTowerMouseY = 480;
	const int SecondTowerMouseX = FirstTowerMouseX + 43;
	const int SecondTowerMouseY = FirstTowerMouseY;

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

