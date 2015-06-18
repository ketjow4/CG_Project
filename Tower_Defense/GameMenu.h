#pragma once
#include <string>
#include "Text.h"
#include "texture.h"
#include "GameConstsDefinitions.h"

#include "Drawing2D.h"

class GameMenu
{
public:
	GameMenu();
	~GameMenu();
	/**
	* Funkcja wyœwietla menu gry.
	* @param gameInProgress czy aktualnie toczy siê gra
	*/
	void Draw(bool gameInProgress);
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
private:
	int mouseHover;
	int textButtonHover;
	bool gameInProgress;
	Text *text;
	Drawing2D draw2D;
	Texture *BackgroundImg;
	// The text controls of the different entries.
	std::string NewGameText;// = "New Game";
	std::string ExitText;// = "Exit";
	std::string ResumeGameText;// = "Resume";


	void DrawTextButtons();
	void DrawResumeGameTextButton();
};


