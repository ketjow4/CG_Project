#include "GameMenu.h"


GameMenu::GameMenu()
{
	mouseHover = 0;
	textButtonHover = DO_NOTHING;
	gameInProgress = false;

	NewGameText = "New Game";
	ExitText = "Exit";
	ResumeGameText = "Resume";

	this->text = new Text(24);
	BackgroundImg = new Texture(GL_TEXTURE_2D, "Menu/background.bmp");
	if (!BackgroundImg->Load())
	{
		std::cout << "Error. Can not load menu background image" << std::endl;
	}
}

void GameMenu::Draw(bool _gameInProgress)
{
	this->gameInProgress = _gameInProgress;

	glClear(GL_COLOR_BUFFER_BIT);

	// przygotowane pod teksture
	//glBegin(GL_QUADS);
	//
	////glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	////glEnable(GL_COLOR_MATERIAL);
	//glColor3f(1.0, 0.0, 0.0);
	//glVertex2f(0.0, 0.0);
	//glVertex2f(640.0, 0.0);
	//glVertex2f(640.0, 480.0);
	//glVertex2f(0.0, 480.0);
	//glEnd();
	//glFlush();

	glDepthMask(GL_FALSE);  // disable writes to Z-Buffer
	glDisable(GL_DEPTH_TEST);  // disable depth-testing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	this->DrawTextButtons();

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

}

void GameMenu::DrawTextButtons()
{
	switch (mouseHover)
	{
		case 1:
			switch (textButtonHover)
			{
			case NEW_GAME:
				this->text->RenderText(this->NewGameText, 260, 350, 1, glm::vec3(0.4f, 0.4f, 0.4f));
				this->DrawResumeGameTextButton();
				this->text->RenderText(this->ExitText, 293, 250, 1, glm::vec3(0, 0, 0));
				//this->text->RenderText("", 0, 0, 1, glm::vec3(0.1f, 0.8f, 0.1f));
				break;
			case END_GAME:
				this->text->RenderText(this->NewGameText, 260, 350, 1, glm::vec3(0, 0, 0));
				this->DrawResumeGameTextButton();
				this->text->RenderText(this->ExitText, 293, 250, 1, glm::vec3(0.4f, 0.4f, 0.4f));
				//this->text->RenderText("", 0, 0, 1, glm::vec3(0.1f, 0.8f, 0.1f));
				break;
			case RESUME_GAME:
				this->text->RenderText(this->NewGameText, 260, 350, 1, glm::vec3(0, 0, 0));
				this->DrawResumeGameTextButton();
				this->text->RenderText(this->ExitText, 293, 250, 1, glm::vec3(0, 0, 0));
				//this->text->RenderText("", 0, 0, 1, glm::vec3(0.1f, 0.8f, 0.1f));
				break;
			}
			break;
		case 0:
			this->text->RenderText(this->NewGameText, 260, 350, 1, glm::vec3(0, 0, 0));
			this->DrawResumeGameTextButton();
			this->text->RenderText(this->ExitText, 293, 250, 1, glm::vec3(0, 0, 0));
			//this->text->RenderText("", 0, 0, 1, glm::vec3(0.1f, 0.8f, 0.1f));	
	}
}

void GameMenu::DrawResumeGameTextButton()
{
	if (this->gameInProgress)
	{
		if (textButtonHover == RESUME_GAME && mouseHover)
			this->text->RenderText(this->ResumeGameText, 272, 300, 1, glm::vec3(0.4f, 0.4f, 0.4f));
		else
			this->text->RenderText(this->ResumeGameText, 272, 300, 1, glm::vec3(0, 0, 0));
	}
	else
		this->text->RenderText(this->ResumeGameText, 272, 300, 1, glm::vec3(0.8f, 0.8f, 0.8f));
}

void GameMenu::CheckMouseMoveAndReact(int x, int y)
{
	if ((x > 261) && (x < 362) && (y>112) && (y < 128))
	{
		this->mouseHover = 1;
		this->textButtonHover = NEW_GAME;
	}
	else if ((x > 273) && (x < 361) && (y>162) && (y < 179))
	{
		this->mouseHover = 1;
		this->textButtonHover = RESUME_GAME;
	}
	else if ((x > 294) && (x < 332) && (y>212) && (y < 228))
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
	if ((x > 261) && (x < 362) && (y>112) && (y < 128))
	{
		return NEW_GAME;
	}
	else if ((x > 273) && (x < 361) && (y>162) && (y < 179))
	{
		return RESUME_GAME;
	}
	else if ((x > 294) && (x < 332) && (y>212) && (y < 228))
	{
		return END_GAME;
	}
	//std::cout << "x: " << x << "y: " << y << std::endl;
	return DO_NOTHING;
}

GameMenu::~GameMenu()
{
	delete BackgroundImg;
	delete text;
}
