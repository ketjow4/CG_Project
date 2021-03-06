#include "GameMenu.h"


GameMenu::GameMenu()
{
	draw2D.Init();

	mouseHover = 0;
	textButtonHover = DO_NOTHING;
	gameInProgress = false;

	NewGameText = "New Game";
	ExitText = "Exit";
	ResumeGameText = "Resume";

	this->text = new Text(24);
	BackgroundImg = new Texture(GL_TEXTURE_2D, "Menu/menu_back.jpg");
	if (!BackgroundImg->Load())
	{
		std::cout << "Error. Can not load menu background image" << std::endl;
	}
}

void GameMenu::Draw(bool _gameInProgress)
{
	this->gameInProgress = _gameInProgress;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//don't change anything below this
	glDepthMask(GL_FALSE);  // disable writes to Z-Buffer
	glDisable(GL_DEPTH_TEST);  // disable depth-testing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//don't change anything above this


	draw2D.Enable();

	draw2D.RenderQuad(0,0,640,480,1,BackgroundImg);				//drawing quad with texture texture must be loaded succesful before

	//draw2D.RenderQuad(250,340,150,40,0,NULL, Vector3f(0.2,1.0,0.0));	//draw regular quad in one color 

	text->Enable();
	this->DrawTextButtons();

	//don't change anything below this
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	//don't change anything above this
}

void GameMenu::DrawTextButtons()
{
	if (mouseHover)
	{
		switch (textButtonHover)
		{
		case NEW_GAME:
			this->text->RenderText(this->NewGameText, 260, 300, 1, glm::vec3(0.4f, 0.4f, 0.4f));
			this->DrawResumeGameTextButton();
			this->text->RenderText(this->ExitText, 293, 200, 1, glm::vec3(0, 0, 0));
			break;
		case END_GAME:
			this->text->RenderText(this->NewGameText, 260, 300, 1, glm::vec3(0, 0, 0));
			this->DrawResumeGameTextButton();
			this->text->RenderText(this->ExitText, 293, 200, 1, glm::vec3(0.4f, 0.4f, 0.4f));
			break;
		case RESUME_GAME:
			this->text->RenderText(this->NewGameText, 260, 300, 1, glm::vec3(0, 0, 0));
			this->DrawResumeGameTextButton();
			this->text->RenderText(this->ExitText, 293, 200, 1, glm::vec3(0, 0, 0));
			break;
		}
	}
	else
	{
		this->text->RenderText(this->NewGameText, 260, 300, 1, glm::vec3(0, 0, 0));
		this->DrawResumeGameTextButton();
		this->text->RenderText(this->ExitText, 293, 200, 1, glm::vec3(0, 0, 0));
	}
}

void GameMenu::DrawResumeGameTextButton()
{
	if (this->gameInProgress)
	{
		if (textButtonHover == RESUME_GAME && mouseHover)
			this->text->RenderText(this->ResumeGameText, 272, 250, 1, glm::vec3(0.4f, 0.4f, 0.4f));
		else
			this->text->RenderText(this->ResumeGameText, 272, 250, 1, glm::vec3(0, 0, 0));
	}
	else
		this->text->RenderText(this->ResumeGameText, 272, 250, 1, glm::vec3(0.8f, 0.8f, 0.8f));
}

void GameMenu::CheckMouseMoveAndReact(int x, int y)
{
	if ((x > 261) && (x < 380) && (y > 162) && (y < 179))
	{
		this->mouseHover = 1;
		this->textButtonHover = NEW_GAME;
	}
	else if ((x > 273) && (x < 361) && (y > 212) && (y < 228))
	{
		this->mouseHover = 1;
		this->textButtonHover = RESUME_GAME;
	}
	else if ((x > 294) && (x < 332) && (y > 262) && (y < 278))
	{
		this->mouseHover = 1;
		this->textButtonHover = END_GAME;
	}
	else
	{
		this->mouseHover = 0;
	}
}

int GameMenu::CheckWhereMouseClickedAndReact(int x, int y)
{
	if ((x > 261) && (x < 380) && (y>162) && (y < 179))
	{
		return NEW_GAME;
	}
	else if ((x > 273) && (x < 361) && (y>212) && (y < 228))
	{
		return RESUME_GAME;
	}
	else if ((x > 294) && (x < 332) && (y>262) && (y < 278))
	{
		return END_GAME;
	}
	return DO_NOTHING;
}

GameMenu::~GameMenu()
{
	delete BackgroundImg;
	delete text;
}
