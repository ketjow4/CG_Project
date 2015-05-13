#include <iostream>


#include "Tower.h"
#include "Camera.h"
#include "Wave.h"
#include "Text.h"
#include "Player.h"

/*Global variables -- temporary*/
int refreshMills = 30;        // refresh interval in milliseconds

long long m_frameTime;
int m_frameCount;
int m_fps;


Camera cam;

Mesh* testObject; 

BasicLightingTechnique* light;		//use this shaders for static objects
SkinningTechnique* m_pEffect;

DirectionalLight m_directionalLight;

Text* text;

vector<Tower*> towerList;

Terrain* terrain;
Path* path;
Wave * wave;


Enemy en;
Enemy en2;
Enemy en3;


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
	m_directionalLight.AmbientIntensity = 0.8f;				//sila swiatla globalnego
	m_directionalLight.DiffuseIntensity = 0.75f;
	m_directionalLight.Direction = Vector3f(1.0f, 0.0, 0.0);

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
	p.SetCamera(Vector3f(cam.eyex, cam.eyey, cam.eyez ), Vector3f(cam.centerx, cam.centery, cam.centerz), cam.m_up);
	p.SetPerspectiveProj(pers);

	wave->p = &p;

	light->Enable();
	
	light->SetWVP(p.GetWVPTrans());
	const Matrix4f& WorldTransformation = p.GetWorldTrans();
	light->SetWorldMatrix(WorldTransformation);
	light->SetDirectionalLight(m_directionalLight);

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
		list<Enemy>::iterator it = wave->enemyList->begin();
		for (; it != wave->enemyList->end(); ++it)
		{
			if (towerList[i]->IsInRange(it->GetPosition()) && it->HP > 0 && it->pathIndex > 0)
			{
				towerList[i]->Shoot(&(*it));
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

	text->RenderText("Tower Defense alpha 0.1",10,10,1,glm::vec3(1,1,1));
	//text->RenderText("Lives: " + Player::getPlayer().Lives ,10,470,1,glm::vec3(1,1,1));
	//text->RenderText("Money" + Player::getPlayer().money,10,440,1,glm::vec3(1,1,1));
	
	
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




int main( int argc, char * argv[] )
{
	Magick::InitializeMagick(*argv);
	// inicjalizacja biblioteki GLUT
	glutInit( & argc, argv );

	// inicjalizacja bufora ramki
	glutInitDisplayMode(  GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA );

	// rozmiary g³ównego okna programu
	glutInitWindowSize( 640, 480 );

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

	initGL(); 

	glewInit();


	light = new BasicLightingTechnique();

	if (!light->Init()) {
		printf("Error initializing the lighting technique\n");
		return -1;
	}

	m_pEffect = new SkinningTechnique();

	if (!m_pEffect->Init()) {
		printf("Error initializing the skinning technique\n");
		//return -1;
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

	//enemy 
	en.light = light;
	en.LoadModel("Models/phoenix_ugv.md2");
	en.terrain = terrain;
	en.path = path;
	en.pathIndex = 0;

	en2.light = light;
	en2.LoadModel("Models/phoenix_ugv.md2");
	en2.terrain = terrain;
	en2.path = path;
	en2.pathIndex = 0;

	en3.light = light;
	en3.LoadModel("Models/phoenix_ugv.md2");
	en3.terrain = terrain;
	en3.path = path;
	en3.pathIndex = 0;

	list<Enemy> enList;
	enList.push_back(en);
	enList.push_back(en2);
	enList.push_back(en3);

	wave = new Wave(&enList,NULL);
	wave->pathDifference = 50;

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

	delete testObject;
	delete terrain;
	delete light;
	delete m_pEffect;
	delete text;
	delete path;
	delete wave;
	for(int i = 0; i < towerList.size(); i++)
		delete towerList[i];

	return 0;
}
