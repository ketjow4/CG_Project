#include <Windows.h>
#include <iostream>
#include <sstream>

#include "Tower.h"
#include "Camera.h"
#include "Text.h"
#include "Player.h"
#include "GameMenu.h"
#include "GameHUD.h"
#include "Player.h"
#include "GameConstsDefinitions.h"
#include "Mouse.h"
#include "PickingTexture.h"
#include "PickingTechnique.h"
#include "Level.h"

#include "ShadowMapFBO.h"
#include "ShadowMapTechnique.h"
#include "BasicLighting.h"

#include "Audio.h"


int refreshMills = 30;
long long m_frameTime;
int m_frameCount;
int m_fps;

Camera* cam;

BasicLightingTechnique* light;		//use this shaders for static objects
SkinningTechnique* m_pEffect;
PickingTexture* m_pickingTexture;
PickingTechnique* m_pickingEffect;
ShadowMapTechnique* m_pShadowMapEffect;
ShadowMapFBO m_shadowMapFBO;

DirectionalLight m_directionalLight;

Text* text;

Level* lvl;
Level* lvl2;

Mouse mouse;
string displayedText = "Tower Defense alpha 0.2";

float m_scale = 0;
static const float FieldDepth = 400.0f;
static const float FieldWidth = 400.0f;

bool gameIsRunning = false;
bool gameInProgress = false;
bool showHud = true;

GameMenu *menu;
GameHUD *hud;
Audio *audio;




SpotLight sl[1];


#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480




void InitGL() 
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);				// Set background color


	glClearDepth(1.0f);									// Set background depth to farthest
	glEnable(GL_DEPTH_TEST);							// Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);								// Set the type of depth-test
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	glEnable( GL_TEXTURE_2D );



	m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
	m_directionalLight.AmbientIntensity = 0.0f;				//sila swiatla globalnego
	m_directionalLight.DiffuseIntensity = 0.0f;
	m_directionalLight.Direction = Vector3f(1.0f, 1.0, 1.0).Normalize();

	cam = new Camera();

	cam->eyey = 200;//100;
	cam->eyex = 256;//256;
	cam->eyez = 0;
	cam->centerx = 1;
	cam->centerz = 1;
	cam->centery = 0;


		sl[0].AmbientIntensity = 0.8f;
        sl[0].DiffuseIntensity = 0.9f;
        sl[0].Color = Vector3f(1.0f, 1.0f, 1.0f);
        sl[0].Attenuation.Linear = 0.001f;
        sl[0].Position  = Vector3f(-100.0, 300.0, -100.0f);
        sl[0].Direction = Vector3f(0.2f, -1.0f, 0.1f);
        //sl[0].Cutoff =  240.0f;

}








void CalcShadow()
{
	m_shadowMapFBO.BindForWriting();

    glClear(GL_DEPTH_BUFFER_BIT);

    m_pShadowMapEffect->Enable();

	PersProjInfo pers;
	pers.FOV = 90;
	pers.Height = WINDOW_HEIGHT;
	pers.Width = WINDOW_WIDTH;
	pers.zFar = 1000.0f;
	pers.zNear = 0.1f;

    Pipeline p;
	p.SetPerspectiveProj(pers);
	
	//p.Scale(1.f, 1.f, 1.f);
	//p.Rotate(0.0f, 0.0f, 0.0f);
	//p.WorldPos(0.f, 0.f, 0.f);
	//p.SetCamera(sl[0].Position, sl[0].Direction, Vector3f(0.0f, 1.0f, 0.0f));
 //   m_pShadowMapEffect->SetWVP(p.GetWVPTrans());
	//lvl->terrain->Render();


	std::list<Enemy*>::iterator it = lvl->currentWave->enemyList->begin();

	for(it ; it != lvl->currentWave->enemyList->end(); it++)
	{
		p.Scale(0.3,0.3,0.3);
		p.Rotate( (*it)->GetRotation());
		p.WorldPos( (*it)->GetPosition());
		p.SetCamera(sl[0].Position, sl[0].Direction, Vector3f(0.0f, 1.0f, 0.0f));
		m_pShadowMapEffect->SetWVP(p.GetWVPTrans());
		(*it)->model->Render();
	}


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	light->Enable();

	light->SetEyeWorldPos(Vector3f(cam->eyex, cam->eyey, cam->eyez));

	

	PersProjInfo pers;
	pers.FOV = 90;
	pers.Height = WINDOW_HEIGHT;
	pers.Width = WINDOW_WIDTH;
	pers.zFar = 1000.0f;
	pers.zNear = 0.1f;
	Pipeline p;	
	p.SetPerspectiveProj(pers);

	

	//m_scale += 0.057;
	//PointLight pl[2];
	//for (int i = 0; i < 2; i++)
	//{
	//	pl[i].DiffuseIntensity = 0.5f;
	//	pl[i].AmbientIntensity = 1.8;
	//	pl[i].Color = Vector3f(0.8f*i, 0.3f*i, 1.0f);
	//	pl[i].Position = Vector3f(-150.0f*i, 1.0f, FieldDepth * (cosf(m_scale) + 1.0f) / 2.0f);
	//	pl[i].Attenuation.Linear = 0.05f;
	//}
	//light->SetPointLights(2, pl);


	p.Rotate(0.0f, 90.0f, 0.0f);
	p.WorldPos(0.0f, 0.0f, 1.0f);
	p.SetCamera(Vector3f(cam->eyex, cam->eyey, cam->eyez), Vector3f(cam->centerx, cam->centery, cam->centerz), cam->m_up);
	p.SetPerspectiveProj(pers);

	lvl->currentWave->p = &p;

	light->Enable();

	light->SetWVP(p.GetWVPTrans());
	const Matrix4f& WorldTransformation = p.GetWorldTrans();
	light->SetWorldMatrix(WorldTransformation);
	light->SetDirectionalLight(m_directionalLight);
	light->SetEyeWorldPos(Vector3f(cam->eyex, cam->eyey, cam->eyez));
	light->SetMatSpecularIntensity(0.5f);
	light->SetMatSpecularPower(2);

	m_pickingTexture->EnableWriting();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pickingEffect->Enable();

	p.Scale(1.f, 1.f, 1.f);
	p.Rotate(0.0f, 0.0f, 0.0f);
	p.WorldPos(0.f, 0.f, 0.f);
	light->SetWVP(p.GetWVPTrans());
	m_pickingEffect->SetWVP(p.GetWVPTrans());
	lvl->terrain->Render();


	m_pickingTexture->DisableWriting();

	m_shadowMapFBO.BindForReading(GL_TEXTURE1);

	if (mouse.leftClick)
	{
		mouse.leftClick = false;

		PickingTexture::PixelInfo Pixel = m_pickingTexture->ReadPixel(mouse.pos2d.x, mouse.pos2d.y);
		mouse.SetPos3d(Pixel.x, Pixel.y, Pixel.z);
		pair<float, float> closest;
		if (mouse.DistToClosest(lvl->path->possibleTowerPoints, closest) < 20.f)
		{
			ostringstream ss;
			ss << " x: " << closest.first <<
				" y: " << lvl->terrain->GetTerrainHeight(closest.first, closest.second) <<
				" z: " << closest.second;
			displayedText = ss.str();

			if ((Player::getPlayer().money >= Tower::cost))
			{
				if ((hud->selectedTower == NO_SELECTION))
				{
					displayedText = "You need to select tower first";
				}
				else
				{
					Tower *tower = new Tower(light, m_pEffect, Vector3f(closest.first, 0, closest.second), lvl->terrain);
					if (hud->selectedTower == FIRST_TOWER)
						tower->LoadModel(11);
					else if (hud->selectedTower == SECOND_TOWER)
						tower->LoadModel(31);
					else
						displayedText = "Not a possible tower position";
					tower->LoadMissile(21);
					lvl->towerList.push_back(tower);
					Player::getPlayer().TowerBuy();
					hud->action = DO_NOTHING;
					hud->selectedTower = NO_SELECTION;
				}
					
			}
		}
		else
			displayedText = "Not a possible tower position";
	}


	light->Enable();

	p.Scale(1.f, 1.f, 1.f);
	p.Rotate(0.0f, 0.0f, 0.0f);
	p.WorldPos(0.f, 0.f, 0.f);
	p.SetCamera(Vector3f(cam->eyex, cam->eyey, cam->eyez), Vector3f(cam->centerx, cam->centery, cam->centerz), cam->m_up);
	light->SetWVP(p.GetWVPTrans());
	light->SetWV(p.GetWVTrans());
	light->SetWorldMatrix(p.GetWorldTrans());

	p.SetCamera(sl[0].Position, sl[0].Direction, Vector3f(0.0f, 1.0f, 0.0f));
    light->SetLightWVP(p.GetWVPTrans());

	

	lvl->terrain->Render();


	p.SetCamera(Vector3f(cam->eyex, cam->eyey, cam->eyez), Vector3f(cam->centerx, cam->centery, cam->centerz), cam->m_up);



	m_pEffect->Enable();
	for (int i = 0; i < lvl->towerList.size(); i++)
	{
		lvl->towerList[i]->Render(&p, cam);
	}

	lvl->currentWave->ClearDead();
	light->Enable();
	lvl->currentWave->UpdatePosition();

	for (int i = 0; i < lvl->towerList.size(); i++)
	{
		list<Enemy*>::iterator it = lvl->currentWave->enemyList->begin();
		for (; it != lvl->currentWave->enemyList->end(); ++it)
		{
			if (lvl->towerList[i]->IsInRange((*it)->GetPosition()) && (*it)->HP > 0 && (*it)->pathIndex > 0)
			{
				lvl->towerList[i]->Shoot(*it);
				break;
			}
		}
		if (lvl->currentWave->enemyList->size() == 0)
		{
			lvl->towerList[i]->distance_to_target = lvl->towerList[i]->Range + 1;		//stop shooting after all enemies are killed
		}
		lvl->towerList[i]->UpdateMissiles(&p, lvl->currentWave->enemyList);
		lvl->towerList[i]->Reload();
	}
	lvl->AdvanceToNextWave();
	//----- end 3D drawing 

	// ---- 2D drawing on screen eg. menu text etc.

	glDepthMask(GL_FALSE);  // disable writes to Z-Buffer				//-------------------do not copy this function calls if you want to draw in 2D do this
	glDisable(GL_DEPTH_TEST);  // disable depth-testing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);																						//after this

	if (showHud)
	{
		text->RenderText(displayedText, 320, 10, 1, glm::vec3(0.2, 0.2, 0.2));
		hud->Draw(lvl->currentWave->enemyList->size());
	}

	if (Player::getPlayer().lives == 0)
	{
		//text->RenderText("GAME OVER", 280, 240, 1, glm::vec3(1, 0, 0));		//add some function to exit to menu
		hud->DrawGameOverInfo();
	}
	if (lvl->IsWon())
	{
		//text->RenderText("CONGRATULATION YOU WON", 150, 240, 1, glm::vec3(0, 1, 0));		//add some function to advance to next
		//text->RenderText("Click 'n' and wait", 200, 200, 1, glm::vec3(1, 1, 1));		//add some function to advance to next
		hud->DrawYouWonInfo();
	}



	glDisable(GL_BLEND);																															//before this
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

}


void GameProgress()
{
	m_frameCount++;

	long long time = GetCurrentTimeMillis();

	if (time - m_frameTime >= 1000) {
		m_frameTime = time;
		m_fps = m_frameCount;
		m_frameCount = 0;
	}
	

	cam->UpdateCamera();

	CalcShadow();
	Render();


}

// funkcja generuj¹ca scenê 3D

void Display()
{
	if (gameIsRunning)
	{
		gameInProgress = true;
		GameProgress();
		glutSwapBuffers();
		if (Player::lives <= 0)
		{
			Sleep(2500);
			gameIsRunning = false;
			gameInProgress = false;
		}
	}
	else
	{
		menu->Draw(gameInProgress);				
		glutSwapBuffers();
	}

	//end of 2D drawing
}

// change window size
void Reshape( int width, int height )
{
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(90.0f, aspect, 0.1f, 1000.0f);		//kat widzenia, aspect ratio, zNear, zFar

	mouse.SetWindowSize(width, height);
	m_pickingTexture->Init(width, height);
	static bool firstReshape = true;
	if (firstReshape)
		firstReshape = false; 
	else
		m_shadowMapFBO.Init(width, height);
}


void timer(int value) 
{
	glutPostRedisplay();					// Post re-paint request to activate display()
	glutTimerFunc(refreshMills, timer, 0);	// next timer call milliseconds later
}


void Keyboard( unsigned char key, int x, int y )
{
	const double angle = 5;
	if( key == 'z')
	{
		cam->Rotate(-angle);	//kat_obrotu += 5;
	}
	if( key == 'x')
	{
		cam->Rotate(angle);	//kat_obrotu -= 5;
	}
	if( key == 'n' && lvl->IsWon())
	{
		lvl->towerList.clear();
		lvl2 = new Level();
		lvl2->LoadFromFile("Levels/level2.txt");
		lvl = lvl2;
	}
}

void SpecialKeys( int key, int x, int y )
{
	const double movementSpeed = 10.0;
	switch( key )
	{
	case GLUT_KEY_LEFT:
		cam->MoveLeft(movementSpeed);
		break;
	case GLUT_KEY_UP:
		cam->MoveForward(movementSpeed);
		break;
	case GLUT_KEY_RIGHT:
		cam->MoveRight(movementSpeed);
		break;
	case GLUT_KEY_DOWN:
		cam->MoveBackward(movementSpeed);
		break;
	}
}

void PrepareNewGame()
{
	Player::getPlayer().Init(1, 100);
	lvl = new Level();
	lvl->cam = cam;
	lvl->LoadFromFile("Levels/level.txt");
}

void ResetGame()
{
	PrepareNewGame();
}

void HandleUserCommand(int menuOption)
{
	switch (menuOption)
	{
	case NEW_GAME:
		gameIsRunning = true;
		ResetGame();
		break;
	case END_GAME:
		std::cout << "End of game" << std::endl;
		throw "EXIT";
		break;
	case PAUSE_GAME:
		if (showHud)
			gameIsRunning = false;
		break;
	case RESUME_GAME:
		if (gameInProgress)
			gameIsRunning = true;
		break;
	case SHOW_HIDE_HUD:
		showHud = !showHud;
		break;
	}
}

void MouseFunc(int button, int state, int x, int y)
{
	int result = DO_NOTHING;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		mouse.MouseLeftClick(x, y);
		if (gameIsRunning)
			result = hud->CheckWhereMouseClickedAndReact(mouse.normalizedPos2d.x, mouse.normalizedPos2d.y);
		else
			result = menu->CheckWhereMouseClickedAndReact(mouse.normalizedPos2d.x, mouse.normalizedPos2d.y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		mouse.MouseRightClick(x, y);
		result = hud->ShowHide();
	}
	if (result != DO_NOTHING)
		HandleUserCommand(result);
}

void MotionFunc(int x, int y)
{
	mouse.MouseMove(x, y);
}

void PassiveMotionFunc(int x, int y)
{
	mouse.MouseMove(x, y);
	if (gameIsRunning)
		hud->CheckMouseMoveAndReact(mouse.normalizedPos2d.x, mouse.normalizedPos2d.y);
	else
		menu->CheckMouseMoveAndReact(mouse.normalizedPos2d.x, mouse.normalizedPos2d.y);
}

void InitGlut(int argc, char * argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);
	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	// rozmiary g³ównego okna programu
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	mouse.SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	// utworzenie g³ównego okna programu
	glutCreateWindow("Tower Defense");
	// do³¹czenie funkcji generuj¹cej scenê 3D
	glutDisplayFunc(Display);
	// do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);
	// do³¹czenie funkcji obs³ugi klawiatury
	glutKeyboardFunc(Keyboard);
	// do³¹czenie funkcji obs³ugi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MotionFunc);
	glutPassiveMotionFunc(PassiveMotionFunc);
}

int main(int argc, char * argv[])
{
	Magick::InitializeMagick(*argv);
	InitGlut(argc, argv);
	InitGL();
	glewInit();

	menu = new GameMenu();
	hud = new GameHUD();

	ModelsContainer::LoadMesh(1, new Mesh, "Models/phoenix_ugv.md2");
	ModelsContainer::LoadMesh(11, new SkinnedMesh(FIRST_TOWER_MATERIAL), "Models/firstTower.md5mesh");
	ModelsContainer::LoadMesh(21, new Mesh, "Models/missile.fbx");
	ModelsContainer::LoadMesh(31, new SkinnedMesh(SEC_TOWER_MATERIAL), "Models/secondTower.md5mesh");

	TerrainsContainer::LoadTerrain(1, "Models/terrain1.bmp", "Models/terrain1texture.bmp", 0.3);
	PathsContainer::LoadPath(1, "Models/path1.bmp");
	TerrainsContainer::LoadTerrain(2, "Models/terrain2.bmp", "Models/terrain2texture.bmp", 0.2);
	PathsContainer::LoadPath(2, "Models/path2.bmp");
	
	if (!m_shadowMapFBO.Init(WINDOW_WIDTH, WINDOW_HEIGHT)) {
		return false;
	}
	m_pShadowMapEffect = new ShadowMapTechnique();
	if (!m_pShadowMapEffect->Init()) {
		printf("Error initializing the shadow map technique\n");
		return false;
	}

	light = Engine::getEngine().getLight();
	light->Init();		//very important
	light->Enable();
	light->SetSpotLights(1, sl);
    light->SetTextureUnit(0);
    light->SetShadowMapTextureUnit(1);


	m_pEffect = Engine::getEngine().getEffect();
	m_pickingTexture = Engine::getEngine().getpickingTexture();
	m_pickingEffect = Engine::getEngine().getpickingEffect();


	m_pEffect->Init();
	m_pickingTexture->Init(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pickingEffect->Init();

	m_pEffect->Enable();
	m_pEffect->SetSpotLights(1,sl);
	

	const Vector4f fogColor(0.5f, 0.5f, 0.5f, 1.f);
	const float fogDensity = 0.003f;
	light->Enable();
	light->SetFogColor(fogColor);
	light->SetFogDensity(fogDensity);
	m_pEffect->Enable();
	m_pEffect->SetFogColor(fogColor);
	m_pEffect->SetFogDensity(fogDensity);

	text = new Text(24);

	glutTimerFunc(0, timer, 0);

	PrepareNewGame();

	audio = new Audio();
	audio->Play();

	try
	{
		glutMainLoop();// wprowadzenie programu do obs³ugi pêtli komunikatów
	}
	catch (const char *msg)
	{
		std::cout << "Game terminated\n";
	}

	delete text;
	for (int i = 0; i < lvl->towerList.size(); i++)
		delete lvl->towerList[i];
	delete m_pShadowMapEffect;
	delete m_pickingEffect;
	delete m_pickingTexture;
	delete m_pEffect;
	delete light;
	delete menu;
	delete hud;
	ModelsContainer::FreeResources();
	TerrainsContainer::FreeResources();
	PathsContainer::FreeResources();

	return 0;
}
