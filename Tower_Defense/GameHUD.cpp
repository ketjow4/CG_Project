#include "GameHUD.h"


GameHUD::GameHUD()
{
	mouseHover = 0;
	textButtonHover = DO_NOTHING;
	this->text = new Text(15);
}


GameHUD::~GameHUD()
{
}

void GameHUD::Draw(const int &enemiesLeft)
{
	// ---- 2D drawing on screen eg. menu text etc.

	//just draw here like in game menu
	////draw2D.Enable();

	////draw2D.RenderQuad(0,0,640,480,1,BackgroundImg);				//drawing quad with texture texture must be loaded succesful before

	////draw2D.RenderQuad(250,340,150,40,0,NULL, Vector3f(0.2,1.0,0.0));	//draw regular quad in one color 


	this->DrawGameInfo(enemiesLeft);
	this->DrawTextButtons();
}

void GameHUD::DrawGameInfo(const int &enemiesLeft)
{
	//text->RenderText("Tower Defense, version ALPHA", 10, 10, 1, glm::vec3(0, 1, 0));
	text->RenderText("PLAYER LIVES : " + std::to_string(Player::getPlayer().lives), 20, 450, 1, glm::vec3(0, 1, 0));
	text->RenderText("ENEMIES LEFT: " + std::to_string(enemiesLeft), 20, 425, 1, glm::vec3(0, 1, 0));
	text->RenderText("YOUR MONEY: " + std::to_string(Player::getPlayer().money) + " $", 450, 450, 1, glm::vec3(0, 1, 0));
}

void GameHUD::DrawTextButtons()
{
	switch (mouseHover)
	{
	case 1:
		switch (textButtonHover)
		{
		case PAUSE_GAME:
			text->RenderText("MENU", 590, 10, 1, glm::vec3(0.9f, 0.9f, 0.9f));
			break;
		}
		break;
	case 0:
		text->RenderText("MENU", 590, 10, 1, glm::vec3(0, 1, 0));
		break;
	}
}

void GameHUD::CheckMouseMoveAndReact(int x, int y)
{
	if ((x > 579) && (x < 633) && (y>458) && (y < 470))
	{
		this->mouseHover = 1;
		this->textButtonHover = PAUSE_GAME;
	}
	else
	{
		this->mouseHover = 0;
	}
}

int GameHUD::CheckWhereMouseClickedAndReact(int x, int y)
{
	if ((x > 579) && (x < 633) && (y>458) && (y < 470))
	{
		return PAUSE_GAME;
	}
}

int GameHUD::ShowHide()
{
	return SHOW_HIDE_HUD;
}
