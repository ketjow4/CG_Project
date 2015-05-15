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

	int mouseHover;
	int textButtonHover;
	bool gameInProgress;

	Text *text;

	// Background
	Texture *BackgroundImg;

	// The text controls of the different entries.
	std::string NewGameText;// = "New Game";
	std::string ExitText;// = "Exit";
	std::string ResumeGameText;// = "Resume";


	void DrawTextButtons();
	void DrawResumeGameTextButton();
	
};


