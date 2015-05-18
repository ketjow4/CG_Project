#include "GameHUD.h"


GameHUD::GameHUD()
{
	mouseHover = 0;
	textButtonHover = DO_NOTHING;
	this->text = new Text(17);
	draw2d.Init();
	MoneyImgBack = new Texture(GL_TEXTURE_2D, "Menu/hud_back.jpg");
	if (!MoneyImgBack->Load())
	{
		std::cout << "Error. Can not load menu background image" << std::endl;
	}
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
	draw2d.Enable();
	draw2d.RenderQuad(0, 454, 640, 26, 1, MoneyImgBack);
	text->RenderText("LIVES: " + std::to_string(Player::getPlayer().lives), 10, 460, 1, glm::vec3(0.8f, 0.8f, 0.8f));
	text->RenderText("ENEMIES: " + std::to_string(enemiesLeft), 110, 460, 1, glm::vec3(0.8f, 0.8f, 0.8f));
	text->RenderText("MONEY: " + std::to_string(Player::getPlayer().money) + " $", 250, 460, 1, glm::vec3(0.8f, 0.8f, 0.8f));
}

void GameHUD::DrawTextButtons()
{
	switch (mouseHover)
	{
	case 1:
		switch (textButtonHover)
		{
		case PAUSE_GAME:
			text->RenderText("MENU", 575, 460, 1, glm::vec3(0.6f, 0.6f, 0.6f));
			break;
		}
		break;
	case 0:
		text->RenderText("MENU", 575, 460, 1, glm::vec3(0.8f, 0.8f, 0.8f));
		break;
	}
}

void GameHUD::CheckMouseMoveAndReact(int x, int y)
{
	if ((x > 573) && (x < 622) && (y>8) && (y < 20))
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
	if ((x > 573) && (x < 622) && (y>8) && (y < 20))
	{
		return PAUSE_GAME;
	}
}

int GameHUD::ShowHide()
{
	return SHOW_HIDE_HUD;
}
