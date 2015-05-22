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
#include "SkinnedShadowTechnique.h"
#include "BasicLighting.h"
#include "Audio.h"

const int refreshMills = 30;
long long m_frameTime;
int m_frameCount;
int m_fps;
BasicLightingTechnique* light;		//use this shaders for static objects
SkinningTechnique* m_pEffect;
PickingTexture* m_pickingTexture;
PickingTechnique* m_pickingEffect;
ShadowMapTechnique* m_pShadowMapEffect;
SkinnedShadowTechnique* m_pSkinnedShadowMapEffect;
ShadowMapFBO* m_shadowMapFBO;

DirectionalLight m_directionalLight;
SpotLight sl[1];
Camera* cam;
PersProjInfo pers;
Text* text;
Level* lvl;
Mouse mouse;
string displayedText = "Tower Defense Release 1.0";

float m_scale = 0;
const float FieldDepth = 400.0f;
const float FieldWidth = 400.0f;
bool gameIsRunning = false;
bool gameInProgress = false;
bool showHud = true;

GameMenu *menu;
GameHUD *hud;
Audio *audio;

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

void InitGL();
void InitGlut(int argc, char * argv[]);
void InitShaders();
void LoadModels();
void FreeResources();

void Display();
void GameProgress();
void CalcShadow();
void ProcessAndRender();
void CalcPickingCoords(Pipeline &p);
void CheckMouseLeftClick();
void RenderTerrain(Pipeline &p);
void RenderTowers(Pipeline &p);
void RenderEnemies(Pipeline &p);
void ProcessAndRenderMissiles(Pipeline &p);
void RenderHud();

void PrepareNewGame();
void ResetGame();
void HandleUserCommand(int menuOption);

void Reshape(int width, int height);
void Timer(int value);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeys(int key, int x, int y);
void MouseFunc(int button, int state, int x, int y);
void MotionFunc(int x, int y);
void PassiveMotionFunc(int x, int y);

int main(int argc, char * argv[])
{
	Magick::InitializeMagick(*argv);
	InitGlut(argc, argv);
	InitGL();
	glewInit();
	InitShaders();
	LoadModels();
	menu = new GameMenu();
	hud = new GameHUD();
	audio = new Audio();
	audio->PlayBackground();
	try
	{
		glutTimerFunc(0, Timer, 0);
		glutMainLoop();// wprowadzenie programu do obs³ugi pêtli komunikatów
	}
	catch (const char *msg)
	{
		std::cout << "Game terminated\n";
	}
	FreeResources();
	return 0;
}

void InitGL()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);				// Set background color
	glClearDepth(1.0f);									// Set background depth to farthest
	glEnable(GL_DEPTH_TEST);							// Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);								// Set the type of depth-test
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	glEnable(GL_TEXTURE_2D);

	m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
	m_directionalLight.AmbientIntensity = 0.0f;				//sila swiatla globalnego
	m_directionalLight.DiffuseIntensity = 0.0f;
	m_directionalLight.Direction = Vector3f(1.0f, 1.0, 1.0).Normalize();

	cam = new Camera();
	cam->eyey = 200;
	cam->eyex = 256;
	cam->eyez = 0;
	cam->centerx = 1;
	cam->centerz = 1;
	cam->centery = 0;

	sl[0].AmbientIntensity = 0.8f;
	sl[0].DiffuseIntensity = 0.9f;
	sl[0].Color = Vector3f(1.0f, 1.0f, 1.0f);
	sl[0].Attenuation.Linear = 0.001f;
	sl[0].Position = Vector3f(-100.0, 300.0, -100.0f);
	sl[0].Direction = Vector3f(0.2f, -1.0f, 0.1f);
	//sl[0].Cutoff =  240.0f;

	pers.FOV = 90;
	pers.Height = WINDOW_HEIGHT;
	pers.Width = WINDOW_WIDTH;
	pers.zFar = 1000.0f;
	pers.zNear = 0.1f;
}

void InitGlut(int argc, char * argv[])
{
	glutInit(&argc, argv);// inicjalizacja biblioteki GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);// inicjalizacja bufora ramki
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);// rozmiary g³ównego okna programu
	mouse.SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Tower Defense");// utworzenie g³ównego okna programu
	glutDisplayFunc(Display);// do³¹czenie funkcji generuj¹cej scenê 3D
	glutReshapeFunc(Reshape);// do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutKeyboardFunc(Keyboard);// do³¹czenie funkcji obs³ugi klawiatury

	// do³¹czenie funkcji obs³ugi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MotionFunc);
	glutPassiveMotionFunc(PassiveMotionFunc);
}

void InitShaders()
{
	const Vector4f fogColor(0.5f, 0.5f, 0.5f, 1.f);
	const float fogDensity = 0.003f;

	m_shadowMapFBO = new ShadowMapFBO();
	if (!m_shadowMapFBO->Init(WINDOW_WIDTH, WINDOW_HEIGHT))
		exit(-1);
	m_pShadowMapEffect = new ShadowMapTechnique();
	if (!m_pShadowMapEffect->Init())
	{
		printf("Error initializing the shadow map technique\n");
		exit(-1);
	}
	m_pSkinnedShadowMapEffect = new SkinnedShadowTechnique();
	if (!m_pSkinnedShadowMapEffect->Init())
	{
		printf("Error initializing the skinned shadow map technique\n");
		exit(-1);
	}

	light = Engine::getEngine().getLight();
	light->Init();		//very important
	light->Enable();
	light->SetSpotLights(1, sl);
	light->SetTextureUnit(0);
	light->SetShadowMapTextureUnit(1);
	light->SetFogColor(fogColor);
	light->SetFogDensity(fogDensity);

	m_pEffect = Engine::getEngine().getEffect();
	m_pEffect->Init();
	m_pEffect->Enable();
	m_pEffect->SetSpotLights(1, sl);
	m_pEffect->SetFogColor(fogColor);
	m_pEffect->SetFogDensity(fogDensity);

	m_pickingTexture = Engine::getEngine().getpickingTexture();
	m_pickingTexture->Init(WINDOW_WIDTH, WINDOW_HEIGHT);

	m_pickingEffect = Engine::getEngine().getpickingEffect();
	m_pickingEffect->Init();

	text = new Text(24);
}

void LoadModels()
{
	ModelsContainer::LoadMesh(1, new Mesh, "Models/phoenix_ugv.md2");
	ModelsContainer::LoadMesh(11, new SkinnedMesh(FIRST_TOWER_MATERIAL), "Models/firstTower.md5mesh");
	ModelsContainer::LoadMesh(21, new Mesh, "Models/grayMissile.fbx");
	ModelsContainer::LoadMesh(12, new SkinnedMesh(SEC_TOWER_MATERIAL), "Models/secondTower.md5mesh");
	ModelsContainer::LoadMesh(22, new Mesh, "Models/greenMissile.fbx");

	TerrainsContainer::LoadTerrain(1, "Models/terrain1.bmp", "Models/terrain1texture.bmp", 0.3);
	PathsContainer::LoadPath(1, "Models/path1.bmp");
	TerrainsContainer::LoadTerrain(2, "Models/terrain2.bmp", "Models/terrain2texture.bmp", 0.2);
	PathsContainer::LoadPath(2, "Models/path2.bmp");
}

void FreeResources()
{
	delete text;
	for (int i = 0; i < lvl->towerList.size(); i++)
		delete lvl->towerList[i];
	delete m_pSkinnedShadowMapEffect;
	delete m_pShadowMapEffect;
	delete m_shadowMapFBO;
	delete m_pickingEffect;
	delete m_pickingTexture;
	delete m_pEffect;
	delete light;
	delete menu;
	delete hud;
	ModelsContainer::FreeResources();
	TerrainsContainer::FreeResources();
	PathsContainer::FreeResources();
}

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
	ProcessAndRender();
}


void CalcShadow()
{
	m_shadowMapFBO->BindForWriting();
	glClear(GL_DEPTH_BUFFER_BIT);

	Pipeline p;
	p.SetPerspectiveProj(pers);

	m_pShadowMapEffect->Enable();
	std::list<Enemy*>::iterator it = lvl->currentWave->enemyList->begin();
	for (it; it != lvl->currentWave->enemyList->end(); it++)
	{
		p.Scale(0.3, 0.3, 0.3);
		p.Rotate((*it)->GetRotation());
		p.WorldPos((*it)->GetPosition());
		p.SetCamera(sl[0].Position, sl[0].Direction, Vector3f(0.0f, 1.0f, 0.0f));
		m_pShadowMapEffect->SetWVP(p.GetWVPTrans());
		(*it)->model->Render();
	}

	m_pSkinnedShadowMapEffect->Enable();
	for (int i = 0; i < lvl->towerList.size(); i++)
	{
		p.Scale(lvl->towerList[i]->GetScale());
		p.Rotate(0, 90, -90);
		p.WorldPos(lvl->towerList[i]->GetPosition());
		p.SetCamera(sl[0].Position, sl[0].Direction, Vector3f(0.0f, 1.0f, 0.0f));
		m_pSkinnedShadowMapEffect->SetWVP(p.GetWVPTrans());
		lvl->towerList[i]->CalcAnimation(m_pSkinnedShadowMapEffect);
		lvl->towerList[i]->model->Render();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ProcessAndRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	Pipeline p;
	p.SetPerspectiveProj(pers);
	p.Rotate(0.0f, 90.0f, 0.0f);
	p.WorldPos(0.0f, 0.0f, 1.0f);
	p.SetCamera(Vector3f(cam->eyex, cam->eyey, cam->eyez), Vector3f(cam->centerx, cam->centery, cam->centerz), cam->m_up);
	p.SetPerspectiveProj(pers);
	lvl->currentWave->p = &p;

	CalcPickingCoords(p);
	CheckMouseLeftClick();

	m_shadowMapFBO->BindForReading(GL_TEXTURE1);
	light->Enable();
	light->SetEyeWorldPos(Vector3f(cam->eyex, cam->eyey, cam->eyez));
	light->SetDirectionalLight(m_directionalLight);
	light->SetEyeWorldPos(Vector3f(cam->eyex, cam->eyey, cam->eyez));
	light->SetMatSpecularIntensity(0.5f);
	light->SetMatSpecularPower(2);

	RenderTerrain(p);
	RenderTowers(p);
	RenderEnemies(p);
	ProcessAndRenderMissiles(p);
	
	lvl->currentWave->ClearDead();
	lvl->AdvanceToNextWave();

	RenderHud();
}

void CalcPickingCoords(Pipeline &p)
{
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
}

void CheckMouseLeftClick()
{
	if (!mouse.leftClick)
		return;
	mouse.leftClick = false;
	PickingTexture::PixelInfo Pixel = m_pickingTexture->ReadPixel(mouse.pos2d.x, mouse.pos2d.y);
	mouse.SetPos3d(Pixel.x, Pixel.y, Pixel.z);
	pair<float, float> closest;
	if (mouse.DistToClosest(lvl->path->possibleTowerPoints, closest) < 20.f)
	{
		if ((Player::getPlayer().money >= Tower::cost))
		{
			if ((hud->selectedTower == NO_SELECTION))
			{
				displayedText = "You need to select tower first";
			}
			else if (lvl->occupiedTowerPoints.find(closest) != lvl->occupiedTowerPoints.end())
			{
				displayedText = "There's already a tower here";
			}
			else
			{
				Tower *tower = new Tower(light, m_pEffect, Vector3f(closest.first, 0, closest.second), lvl->terrain);
				lvl->occupiedTowerPoints.insert(closest);
				if (hud->selectedTower == FIRST_TOWER)
				{
					tower->LoadModel(11);
					tower->LoadMissile(21);
				}
				else if (hud->selectedTower == SECOND_TOWER)
				{
					tower->LoadModel(12);
					tower->LoadMissile(22);
				}
				lvl->towerList.push_back(tower);
				Player::getPlayer().TowerBuy();
				hud->action = DO_NOTHING;
				hud->selectedTower = NO_SELECTION;
			}

		}
	}
}
void RenderTerrain(Pipeline &p)
{
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
}

void RenderTowers(Pipeline &p)
{
	m_pEffect->Enable();		//leave it here
	for (int i = 0; i < lvl->towerList.size(); i++)
	{
		lvl->towerList[i]->Render(&p, cam);
	}
}

void RenderEnemies(Pipeline &p)
{
	light->Enable();
	lvl->currentWave->UpdatePosition();
}

void ProcessAndRenderMissiles(Pipeline &p)
{
	for (int i = 0; i < lvl->towerList.size(); i++)
	{
		list<Enemy*>::iterator it = lvl->currentWave->enemyList->begin();
		for (; it != lvl->currentWave->enemyList->end(); ++it)
		{
			if (lvl->towerList[i]->IsInRange((*it)->GetPosition()) && (*it)->HP > 0 && (*it)->GetPathIndex() > 0)
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
}

void RenderHud()
{
	glDepthMask(GL_FALSE);  // disable writes to Z-Buffer
	glDisable(GL_DEPTH_TEST);  // disable depth-testing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (showHud)
	{
		text->RenderText(displayedText, 320, 10, 1, glm::vec3(0.2, 0.2, 0.2));
		hud->Draw(lvl->currentWave->enemyList->size());
	}

	if (Player::getPlayer().lives == 0)
		hud->DrawGameOverInfo();
	if (lvl->IsWon())
		hud->DrawYouWonInfo();

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}

void PrepareNewGame()
{
	Player::getPlayer().Init(3, 30);
	//delete lvl;
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

// Change window size
void Reshape(int width, int height)
{
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;// To prevent divide by 0
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
	m_shadowMapFBO->Init(width, height);
}

void Timer(int value)
{
	glutPostRedisplay();					// Post re-paint request to activate display()
	glutTimerFunc(refreshMills, Timer, 0);	// next Timer call milliseconds later
}

void Keyboard(unsigned char key, int x, int y)
{
	const double angle = 5;
	if (key == 'z')
	{
		cam->Rotate(-angle);//kat_obrotu += 5;
	}
	if (key == 'x')
	{
		cam->Rotate(angle);	//kat_obrotu -= 5;
	}
	if (key == 'n' && lvl->IsWon())
	{
		lvl->towerList.clear();
		Level *pLvl = new Level();
		pLvl->cam = cam;
		pLvl->LoadFromFile("Levels/level2.txt");
		delete lvl;
		lvl = pLvl;
	}
}

void SpecialKeys(int key, int x, int y)
{
	const double movementSpeed = 10.0;
	switch (key)
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
	else if (state == GLUT_DOWN)
		audio->MouseClick();
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
