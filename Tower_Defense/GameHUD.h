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
	int  ShowHide();

	int selectedTower;

private:

	int mouseHover;
	int buttonHover;
	int action;
	Drawing2D draw2d;

	Text *text;
	Text *text14;

	Texture *BackgroundImg;
	Texture *FirstTowerImg;
	Texture *FirstTowerImgHover;
	Texture *FirstTowerImgClick;
	Texture *GameOver;

	// The text controls of the different entries.
	std::string NewGameText;
	std::string ExitText;
	std::string ResumeGameText;

	void DrawGameInfo(const int &enemiesLeft);
	void DrawButtons();
	void DrawTextureButtons();

};

