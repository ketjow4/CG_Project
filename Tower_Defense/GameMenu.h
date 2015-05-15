#pragma once
#include <string>
#include "Text.h"
#include "texture.h"
#include "GameConstsDefinitions.h"

class GameMenu
{
public:
	GameMenu();
	~GameMenu();

	void Draw(bool gameInProgress);
	int CheckWhereMouseClickedAndReact(int x, int y);
	void CheckMouseMoveAndReact(int x, int y);

private:

	int mouseHover = 0;
	int textButtonHover = DO_NOTHING;
	bool gameInProgress = false;

	Text *text;

	// Background
	Texture *BackgroundImg;

	// The text controls of the different entries.
	const std::string NewGameText = "New Game";
	const std::string ExitText = "Exit";
	const std::string ResumeGameText = "Resume";


	void DrawTextButtons();
	void DrawResumeGameTextButton();
	
};


