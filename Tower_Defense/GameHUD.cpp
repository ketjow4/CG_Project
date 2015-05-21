#include "GameHUD.h"

GameHUD::GameHUD()
{
	mouseHover = 0;
	buttonHover = DO_NOTHING;
	action = DO_NOTHING;
	selectedTower = NO_SELECTION;

	this->text = new Text(17);
	this->text14 = new Text(14);
	draw2d.Init();
	BackgroundImg = new Texture(GL_TEXTURE_2D, "Menu/hud_back.jpg");
	if (!BackgroundImg->Load())
	{
		std::cout << "Error. Can not load menu background image" << std::endl;
	}
	FirstTowerImg = new Texture(GL_TEXTURE_2D, "Menu/firstTower.jpg");
	if (!FirstTowerImg->Load())
	{
		std::cout << "Error. Can not load first tower image" << std::endl;
	}
	FirstTowerImgHover = new Texture(GL_TEXTURE_2D, "Menu/firstTowerHover.jpg");
	if (!FirstTowerImgHover->Load())
	{
		std::cout << "Error. Can not load first tower hover image" << std::endl;
	}
	FirstTowerImgClick = new Texture(GL_TEXTURE_2D, "Menu/firstTowerClick.jpg");
	if (!FirstTowerImgClick->Load())
	{
		std::cout << "Error. Can not load first tower clicked image" << std::endl;
	}
	SecondTowerImg = new Texture(GL_TEXTURE_2D, "Menu/secTower.jpg");
	if (!SecondTowerImg->Load())
	{
		std::cout << "Error. Can not load second tower image" << std::endl;
	}
	SecondTowerImgHover = new Texture(GL_TEXTURE_2D, "Menu/secTowerHover.jpg");
	if (!SecondTowerImgHover->Load())
	{
		std::cout << "Error. Can not load second tower hover image" << std::endl;
	}
	SecondTowerImgClick = new Texture(GL_TEXTURE_2D, "Menu/secTowerClicked.jpg");
	if (!SecondTowerImgClick->Load())
	{
		std::cout << "Error. Can not load second tower clicked image" << std::endl;
	}
	GameOver = new Texture(GL_TEXTURE_2D, "Menu/GameOverBig.png");
	if (!GameOver->Load())
	{
		std::cout << "Error. Can not load game over image" << std::endl;
	}
	YouWon = new Texture(GL_TEXTURE_2D, "Menu/youWon.png");
	if (!YouWon->Load())
	{
		std::cout << "Error. Can not load you won image" << std::endl;
	}
}

GameHUD::~GameHUD()
{
	delete GameOver;
	delete YouWon;
	delete FirstTowerImg;
	delete FirstTowerImgClick;
	delete FirstTowerImgHover;
	delete SecondTowerImg;
	delete SecondTowerImgHover;
	delete SecondTowerImgClick;
	delete BackgroundImg;
	delete text;
	delete text14;
}

void GameHUD::Draw(const int &enemiesLeft)
{
	// ---- 2D drawing on screen eg. menu text etc.

	//just draw here like in game menu
	////draw2D.Enable();

	////draw2D.RenderQuad(0,0,640,480,1,BackgroundImg);				//drawing quad with texture texture must be loaded succesful before

	////draw2D.RenderQuad(250,340,150,40,0,NULL, Vector3f(0.2,1.0,0.0));	//draw regular quad in one color 
	draw2d.Enable();
	this->DrawGameInfo(enemiesLeft);
	this->DrawButtons();
}

void GameHUD::DrawTextureButtons()
{
	switch (action)
	{
	case FIRST_TOWER_HOVER:
		text14->RenderText("Simple Tower", FirstTowerX, FirstTowerY + 60, 1, glm::vec3(0.2, 0.2, 0.2));
		draw2d.RenderQuad(FirstTowerX, FirstTowerY, 43, 59, 1, FirstTowerImgHover);
		draw2d.RenderQuad(SecondTowerX, SecondTowerY, 43, 59, 1, SecondTowerImg);
		action = DO_NOTHING;
		break;
	case SEC_TOWER_HOVER:
		text14->RenderText("Toxic Tower", FirstTowerX, SecondTowerY + 60, 1, glm::vec3(0.2, 0.2, 0.2));
		draw2d.RenderQuad(FirstTowerX, FirstTowerY, 43, 59, 1, FirstTowerImg);
		draw2d.RenderQuad(SecondTowerX, SecondTowerY, 43, 59, 1, SecondTowerImgHover);
		action = DO_NOTHING;
		break;
	case FIRST_TOWER_CLICKED:
		draw2d.RenderQuad(FirstTowerX, FirstTowerY, 43, 59, 1, FirstTowerImgClick);
		draw2d.RenderQuad(SecondTowerX, SecondTowerY, 43, 59, 1, SecondTowerImg);
		break;
	case SEC_TOWER_CLICKED:
		draw2d.RenderQuad(FirstTowerX, FirstTowerY, 43, 59, 1, FirstTowerImg);
		draw2d.RenderQuad(SecondTowerX, SecondTowerY, 43, 59, 1, SecondTowerImgClick);
		break;
	case DO_NOTHING:
		draw2d.RenderQuad(FirstTowerX, FirstTowerY, 43, 59, 1, FirstTowerImg);
		draw2d.RenderQuad(SecondTowerX, SecondTowerY, 43, 59, 1, SecondTowerImg);
	}
}

void GameHUD::DrawGameOverInfo()
{
	draw2d.RenderQuad(0, 0, 640, 480, 1, GameOver);
}

void GameHUD::DrawYouWonInfo()
{
	draw2d.RenderQuad(0, 0, 640, 480, 1, YouWon);
}

void GameHUD::DrawGameInfo(const int &enemiesLeft)
{
	//text->RenderText("Tower Defense, version ALPHA", 10, 10, 1, glm::vec3(0, 1, 0));
	draw2d.RenderQuad(0, 454, 640, 26, 1, BackgroundImg);
	text->RenderText("LIVES: " + std::to_string(Player::getPlayer().lives), 10, 460, 1, glm::vec3(0.8f, 0.8f, 0.8f));
	text->RenderText("ENEMIES: " + std::to_string(enemiesLeft), 110, 460, 1, glm::vec3(0.8f, 0.8f, 0.8f));
	text->RenderText("MONEY: " + std::to_string(Player::getPlayer().money) + " $", 250, 460, 1, glm::vec3(0.8f, 0.8f, 0.8f));
}

void GameHUD::DrawButtons()
{
	if (mouseHover)
	{
		switch (buttonHover)
		{
		case PAUSE_GAME:
			text->RenderText("MENU", 585, 460, 1, glm::vec3(0.6f, 0.6f, 0.6f));
			break;
		case SEC_TOWER_HOVER:
			text->RenderText("MENU", 585, 460, 1, glm::vec3(0.8f, 0.8f, 0.8f));
			if (action != FIRST_TOWER_CLICKED && action != SEC_TOWER_CLICKED)
				action = SEC_TOWER_HOVER;
			break;
		case FIRST_TOWER_HOVER:
			text->RenderText("MENU", 585, 460, 1, glm::vec3(0.8f, 0.8f, 0.8f));
			if( action != FIRST_TOWER_CLICKED && action != SEC_TOWER_CLICKED)
				action = FIRST_TOWER_HOVER;
			break;
		}
	}
	else{
		text->RenderText("MENU", 585, 460, 1, glm::vec3(0.8f, 0.8f, 0.8f));
	}
	this->DrawTextureButtons();
}

void GameHUD::CheckMouseMoveAndReact(int x, int y)
{
	if ((x > 583) && (x < 632) && (y>8) && (y < 20))
	{
		this->mouseHover = 1;
		this->buttonHover = PAUSE_GAME;
	}
	else if ((x > FirstTowerMouseX) && (x < FirstTowerMouseX + 43) && (y > FirstTowerMouseY - 59) && (y < FirstTowerMouseY))
	{
		this->mouseHover = 1;
		this->buttonHover = FIRST_TOWER_HOVER;
	}
	else if ((x > SecondTowerMouseX) && (x < SecondTowerMouseX + 43) && (y > SecondTowerMouseY - 59) && (y < SecondTowerMouseY))
	{
		this->mouseHover = 1;
		this->buttonHover = SEC_TOWER_HOVER;
	}
	else
	{
		this->mouseHover = 0;
	}
}

int GameHUD::CheckWhereMouseClickedAndReact(int x, int y)
{
	if ((x > 583) && (x < 632) && (y>8) && (y < 20))
	{
		return PAUSE_GAME;
	}
	else if ((x > FirstTowerMouseX) && (x < FirstTowerMouseX + 43) && (y > FirstTowerMouseY - 59) && (y < FirstTowerMouseY))
	{
		switch (action)
		{
		case FIRST_TOWER_CLICKED:
			action = DO_NOTHING;
			selectedTower = NO_SELECTION;
			break;
		case SEC_TOWER_CLICKED:
			action = DO_NOTHING;
			selectedTower = FIRST_TOWER;
			break;
		default:
			action = FIRST_TOWER_CLICKED;
			selectedTower = FIRST_TOWER;
			break;
		}
		return DO_NOTHING;
	}
	else if ((x > SecondTowerMouseX) && (x < SecondTowerMouseX + 43) && (y > SecondTowerMouseY - 59) && (y < SecondTowerMouseY))
	{
		switch (action)
		{
		case FIRST_TOWER_CLICKED:
			action = DO_NOTHING;
			selectedTower = SECOND_TOWER;
			break;
		case SEC_TOWER_CLICKED:
			action = DO_NOTHING;
			selectedTower = NO_SELECTION;
			break;
		default:
			action = SEC_TOWER_CLICKED;
			selectedTower = SECOND_TOWER;
			break;
		}
	}
	//std::cout << "x " << x << "y " << y << std::endl;
}

int GameHUD::ShowHide()
{
	return SHOW_HIDE_HUD;
}
