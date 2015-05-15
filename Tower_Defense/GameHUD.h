#pragma once
#include <string>
#include "Text.h"
#include "texture.h"
#include "GameConstsDefinitions.h"
#include "Player.h"

class GameHUD
{
public:
	GameHUD();
	~GameHUD();

	void Draw(const int &enemiesLeft);
	int  CheckWhereMouseClickedAndReact(int x, int y);
	void CheckMouseMoveAndReact(int x, int y);
	int  ShowHide();

private:

	int mouseHover = 0;
	int textButtonHover = DO_NOTHING;

	Text *text;

	// Background
	Texture *BackgroundImg;

	// The text controls of the different entries.
	std::string NewGameText;
	std::string ExitText;
	std::string ResumeGameText;

	void DrawGameInfo(const int &enemiesLeft);
	void DrawTextButtons();

};

