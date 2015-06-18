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
	* Funkcja wy�wietla menu gry.
	* @param gameInProgress czy aktualnie toczy si� gra
	*/
	void Draw(bool gameInProgress);
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


