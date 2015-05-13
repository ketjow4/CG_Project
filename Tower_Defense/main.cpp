#include <iostream>


#include "Tower.h"
#include "Camera.h"
#include "Wave.h"
#include "Text.h"

#include "Player.h"

#include "Mouse.h"
#include "PickingTexture.h"
#include "PickingTechnique.h"
#include <sstream>


/*Global variables -- temporary*/
int refreshMills = 30;        // refresh interval in milliseconds

long long m_frameTime;
int m_frameCount;
int m_fps;


Camera cam;

Mesh* testObject; 

BasicLightingTechnique* light;		//use this shaders for static objects
SkinningTechnique* m_pEffect;
PickingTexture* m_pickingTexture;
PickingTechnique* m_pickingEffect;


DirectionalLight m_directionalLight;

Text* text;

vector<Tower*> towerList;

Terrain* terrain;
Path* path;
Wave * wave;

Mouse mouse;

string displayedText = "Tower Defense alpha 0.1";


void initGL() 
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);				// Set background color
	glClearDepth(1.0f);									// Set background depth to farthest
	glEnable(GL_DEPTH_TEST);							// Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);								// Set the type of depth-test
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	glEnable( GL_TEXTURE_2D );

	m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
	m_directionalLight.AmbientIntensity = 0.5f;				//sila swiatla globalnego
	m_directionalLight.DiffuseIntensity = 0.5f;
	m_directionalLight.Direction = Vector3f(1.0f, 1.0, 1.0).Normalize();

	cam.eyey = 200;//100;
	cam.eyex = 256;//250;
	cam.eyez = 0;
	cam.centerx = 1;
	cam.centerz = 1;
	cam.centery = 0;


}

// funkcja generuj¹ca scenê 3D
void Display()
{
	m_frameCount++;

	long long time = GetCurrentTimeMillis();

	if (time - m_frameTime >= 1000) {
		m_frameTime = time;
		m_fps = m_frameCount;
		m_frameCount = 0;
	}

	cam.UpdateCamera();
	glDisable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	//start of 3d Drawing

	PersProjInfo pers;
	pers.FOV = 90;
	pers.Height = 480;
	pers.Width = 640;
	pers.zFar = 1000.0f;
	pers.zNear = 0.1f;
	Pipeline p;
	p.Scale(0.1f, 0.1f, 0.1f);
	p.Rotate(0.0f,90.0f, 0.0f);
	p.WorldPos(0.0f, 0.0f, 10.0f);
	p.SetCamera(Vector3f(cam.eyex, cam.eyey, cam.eyez), Vector3f(cam.centerx, cam.centery, cam.centerz), cam.m_up);
	p.SetPerspectiveProj(pers);

	wave->p = &p;

	light->Enable();
	
	light->SetWVP(p.GetWVPTrans());
	const Matrix4f& WorldTransformation = p.GetWorldTrans();
	light->SetWorldMatrix(WorldTransformation);
	light->SetDirectionalLight(m_directionalLight);

	m_pickingTexture->EnableWriting();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pickingEffect->Enable();

	p.Scale(1.f, 1.f, 1.f);
	p.Rotate(0.0f, 0.0f, 0.0f);
	p.WorldPos(0.f, 0.f, 0.f);
	light->SetWVP(p.GetWVPTrans());
	m_pickingEffect->SetWVP(p.GetWVPTrans());
	terrain->Render();

	m_pickingTexture->DisableWriting();

	if (mouse.leftClick)
	{
		mouse.leftClick = false;

		PickingTexture::PixelInfo Pixel = m_pickingTexture->ReadPixel(mouse.pos2d.x, mouse.pos2d.y);
		mouse.SetPos3d(Pixel.x, Pixel.y, Pixel.z);
		pair<float, float> closest;
		if (mouse.DistToClosest(path->possibleTowerPoints, closest) < 20.f)
		{
			ostringstream ss;
			ss << " x: " << closest.first <<
				" y: " << terrain->GetTerrainHeight(closest.first, closest.second) <<
				" z: " << closest.second;
			displayedText = ss.str();
		}
		else
			displayedText = "Not a possible tower position";
	}

	light->Enable();
	p.Scale(1.f, 1.f, 1.f);
	p.Rotate(0.0f, 0.0f, 0.0f);
	p.WorldPos(0.f, 0.f, 0.f);
	light->SetWVP(p.GetWVPTrans());
	terrain->Render();

	// Possible tower positions
	vector<pair<float, float>> &towerPoints = path->possibleTowerPoints;
	for (int i = 0; i < towerPoints.size(); ++i)
	{
		float x = towerPoints[i].first;
		float z = towerPoints[i].second;
		p.Scale(0.5f, 1.f, 0.1f);
		p.WorldPos(x, terrain->GetTerrainHeight(x, z), z);
		light->SetWVP(p.GetWVPTrans());
		testObject->Render();
	}


	for(int i = 0; i < towerList.size(); i++)
	{
		towerList[i]->CalcAnimation();
		towerList[i]->Render(&p);
	}

	wave->ClearDead();			
	light->Enable();
	wave->UpdatePosition();

	for(int i = 0; i < towerList.size(); i++)
	{
		list<Enemy*>::iterator it = wave->enemyList->begin();
		for (; it != wave->enemyList->end(); ++it)
		{
			if (towerList[i]->IsInRange((*it)->GetPosition()) && (*it)->HP > 0 && (*it)->pathIndex > 0)
			{
				towerList[i]->Shoot(*it);
				break;
			}
		}
		if( wave->enemyList->size() == 0)
		{
			towerList[i]->distance_to_target = towerList[i]->Range + 1;		//stop shooting after all enemies are killed
		}
		towerList[i]->UpdateMissiles(&p, wave->enemyList);
		towerList[i]->Reload();
	}


	//----- end 3D drawing 

	// ---- 2D drawing on screen eg. menu text etc.
	glDepthMask(GL_FALSE);  // disable writes to Z-Buffer
	glDisable(GL_DEPTH_TEST);  // disable depth-testing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  


	//text->RenderText("Tower Defense alpha 0.1",10,10,1,glm::vec3(1,1,1));
	//text->RenderText("Lives: " + Player::getPlayer().Lives ,10,470,1,glm::vec3(1,1,1));
	//text->RenderText("Money" + Player::getPlayer().money,10,440,1,glm::vec3(1,1,1));

	text->RenderText(displayedText,10,10,1,glm::vec3(1,1,1));

	
	
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	//end of 2D drawing

	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)


	//cout << glGetError() << endl;
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
}


void timer(int value) {
	glutPostRedisplay();					// Post re-paint request to activate display()
	glutTimerFunc(refreshMills, timer, 0);	// next timer call milliseconds later
}


void Keyboard( unsigned char key, int x, int y )
{
	double angle = 5;
	if( key == 'z')
	{
		cam.Rotate(-angle);	//kat_obrotu += 5;
	}
	if( key == 'x')
	{
		cam.Rotate(angle);	//kat_obrotu -= 5;
	}

	// odrysowanie okna
	Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}

//Dzia³a nie tykaæ
void SpecialKeys( int key, int x, int y )
{
	double movementSpeed = 10.0;

	switch( key )
	{
		// kursor w lewo
	case GLUT_KEY_LEFT:
		cam.MoveLeft(movementSpeed);
		break;
		// kursor w górê
	case GLUT_KEY_UP:
		cam.MoveForward(movementSpeed);
		break;
		// kursor w prawo
	case GLUT_KEY_RIGHT:
		cam.MoveRight(movementSpeed);
		break;
		// kursor w dó³
	case GLUT_KEY_DOWN:
		cam.MoveBackward(movementSpeed);
		break;
	}
	// odrysowanie okna
	Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}

void MouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON || state == GLUT_UP)
		mouse.MouseLeftClick(x, y);
	else if (button == GLUT_RIGHT_BUTTON || state == GLUT_UP)
		mouse.MouseRightClick(x, y);
}

void MotionFunc(int x, int y)
{
	mouse.MouseMove(x, y);
}


int main( int argc, char * argv[] )
{
	Magick::InitializeMagick(*argv);
	// inicjalizacja biblioteki GLUT
	glutInit( & argc, argv );

	// inicjalizacja bufora ramki
	glutInitDisplayMode(  GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA );

	// rozmiary g³ównego okna programu
	glutInitWindowSize( 640, 480 );
	mouse.SetWindowSize(640, 480);

	// utworzenie g³ównego okna programu
	glutCreateWindow( "Tower Defense" );

	// do³¹czenie funkcji generuj¹cej scenê 3D
	glutDisplayFunc( Display );

	// do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutReshapeFunc( Reshape );

	// do³¹czenie funkcji obs³ugi klawiatury
	glutKeyboardFunc( Keyboard );

	// do³¹czenie funkcji obs³ugi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc( SpecialKeys );

	glutMouseFunc(MouseFunc);
	glutMotionFunc(MotionFunc);

	initGL(); 

	glewInit();

	light = new BasicLightingTechnique();
	if (!light->Init())
	{
		printf("Error initializing the lighting technique\n");
		return -1;
	}

	m_pEffect = new SkinningTechnique();
	if (!m_pEffect->Init())
	{
		printf("Error initializing the skinning technique\n");
		//return -1;
	}

	m_pickingTexture = new PickingTexture();
	if (!m_pickingTexture->Init(640, 480))
	{
		printf("Error initializing the picking texture\n");
		return -1;
	}

	m_pickingEffect = new PickingTechnique();
	if (!m_pickingEffect->Init())
	{
		printf("Error initializing the picking technique\n");
		return -1;
	}


	light->Enable();

	testObject = new Mesh();
	if (testObject->LoadMesh("Models/phoenix_ugv.md2"))
	{
		cout << "Test object loaded successful " << endl;
	}

	terrain = new Terrain();
	terrain->Init("Models/terrain1.bmp", 0.3f);

	path = new Path();
	path->Init("Models/path1.bmp");

	//enemies
	list<Enemy*> enList;

	Enemy *en = new Enemy();
	en->light = light;
	en->LoadModel(1, "Models/phoenix_ugv.md2");
	en->terrain = terrain;
	en->path = path;
	enList.push_back(en);
	
	en = new Enemy();
	en->light = light;
	en->LoadModel(1, "Models/phoenix_ugv.md2");
	en->terrain = terrain;
	en->path = path;
	enList.push_back(en);

	en = new Enemy();
	en->light = light;
	en->LoadModel(1, "Models/phoenix_ugv.md2");
	en->terrain = terrain;
	en->path = path;
	enList.push_back(en);

	wave = new Wave(&enList, 0, 50);

	vector<pair<float, float>> &towerPoints = path->possibleTowerPoints;
	for (int i = 0; i < towerPoints.size(); ++i)
	{
		float x = towerPoints[i].first;
		float z = towerPoints[i].second;
		towerList.push_back(new Tower(light, m_pEffect, Vector3f(x, 0, z), terrain));
	}

	for(int i = 0; i < towerList.size(); i++)
	{
		towerList[i]->LoadModel("Models/firstTower.md5mesh");
		towerList[i]->LoadMissile("Models/missile.fbx");
	}


	text = new Text(24);

	glutTimerFunc(0, timer, 0);

	//Player::getPlayer().Lives = 10;
	//Player::getPlayer().money = 0;

	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();

	delete text;
	for (int i = 0; i < towerList.size(); i++)
		delete towerList[i];
	delete wave;
	delete path;
	delete terrain;
	delete testObject;
	delete m_pickingEffect;
	delete m_pickingTexture;
	delete m_pEffect;
	delete light;
	ModelsContainer::FreeResources();

	return 0;
}
