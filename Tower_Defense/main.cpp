#include <iostream>


#include "Model.h"
#include "Camera.h"
#include "basic_lighting.h"
#include "pipeline.h"
#include "skinning_technique.h"
#include "Terrain.h"
#include "Path.h"


/*Global variables -- temporary*/
int refreshMills = 15;        // refresh interval in milliseconds

long long m_frameTime;
long long m_startTime;
int m_frameCount;
int m_fps;


Camera cam;

Mesh* object; 

BasicLightingTechnique* light;

DirectionalLight m_directionalLight;


Terrain* terrain;
Path* path;

//SkinnedMesh m_mesh;

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
    m_directionalLight.AmbientIntensity = 1.0f;				//sila swiatla globalnego
	m_directionalLight.DiffuseIntensity = 0.75f;
    m_directionalLight.Direction = Vector3f(1.0f, 0.0, 0.0);

	cam.eyey = 256;//100;
	cam.eyex = 256;//250;
	cam.eyez = 0;
	cam.centerx = 256;
	cam.centerz = 256;
	cam.centery = 0;
}


void camUpdate()
{

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

	

    light->SetWVP(p.GetWVPTrans());
	const Matrix4f& WorldTransformation = p.GetWorldTrans();
    light->SetWorldMatrix(WorldTransformation);
    light->SetDirectionalLight(m_directionalLight);

	p.Scale(1.f, 1.f, 1.f);
	p.Rotate(0.0f, 0.0f, 0.0f);
	p.WorldPos(0.f, 0.f, 0.f);
	light->SetWVP(p.GetWVPTrans());
	terrain->Render();

	
	static int pathIndex = 0;
	p.Scale(0.1f, 0.1f, 0.1f);
	p.Rotate(0.0f,0.0f, 0.0f);
	float x = path->pathPoints[pathIndex].first;
	float z = path->pathPoints[pathIndex].second;
	float y = terrain->GetTerrainHeight(x, z);
	p.WorldPos(x,y,z);
	light->SetWVP(p.GetWVPTrans());
	object->Render();

	if (++pathIndex >= path->pathPoints.size())
		pathIndex = 0;

	p.Scale(0.5f, 0.5f, 0.5f);
	p.WorldPos(0.0f,-90.0f,0.0f);
	light->SetWVP(p.GetWVPTrans());
	//terain->Render();
	
	
	glFlush();

	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)


	//cout << glGetError() << endl;
}

// zmiana wielkoœci okna
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
	//gluPerspective(90.0f, aspect, 0.1f, 1000.0f);		//kat widzenia, aspect ratio, zNear, zFar
	glOrtho(-1000, 1000, -1000, 1000, -1000, 1000);
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
	double movementSpeed = 50.0;

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
	object = new Mesh();
	//terain = new Mesh();

	/*if(terain->LoadMesh("Models/Small/SmallTropicalIsland.obj"))
	{
		cout << "udalos sie wczystac teren" << endl;
	}*/

	if (!light->Init()) {
            printf("Error initializing the lighting technique\n");
            return -1;
        }

	light->Enable();
	//camInit();


	if( object->LoadMesh("Models/phoenix_ugv.md2") )
	{
		cout << "udalo sie wczytac" << endl;
	}

	terrain = new Terrain();
	terrain->Init("Models/terrain1.bmp", 0.15f);

	path = new Path();
	path->Init("Models/path1.bmp");



	glutTimerFunc(0, timer, 0);


	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();

	delete object;

	return 0;
}
