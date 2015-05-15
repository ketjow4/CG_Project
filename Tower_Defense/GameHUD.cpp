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
	//glDepthMask(GL_FALSE);  // disable writes to Z-Buffer
	//glDisable(GL_DEPTH_TEST);  // disable depth-testing
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	this->DrawGameInfo(enemiesLeft);
	this->DrawTextButtons();

	//glDisable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);
	//end of 2D drawing
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
	if ((x > 579) && (x < 628) && (y>458) && (y < 470))
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
	if ((x > 579) && (x < 628) && (y>458) && (y < 470))
	{
		return PAUSE_GAME;
	}
}

int GameHUD::ShowHide()
{
	return SHOW_HIDE_HUD;
}
