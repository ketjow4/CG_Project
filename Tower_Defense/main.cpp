#include <iostream>


//#include "Model.h"
//#include "Camera.h"
//#include "basic_lighting.h"
//#include "pipeline.h"
//#include "skinning_technique.h"
//#include "skinned_mesh.h"
//#include "Terrain.h"
//#include "Path.h"
#include "Tower.h"
#include "Enemy.h"


/*Global variables -- temporary*/
int refreshMills = 30;        // refresh interval in milliseconds

long long m_frameTime;
int m_frameCount;
int m_fps;


Camera cam;

Mesh* object; 

BasicLightingTechnique* light;

DirectionalLight m_directionalLight;

Tower* tow;


Terrain* terrain;
Path* path;


SkinningTechnique* m_pEffect;

Enemy en;

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

	cam.eyey = 200;//100;
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

	


	/*m_pEffect->Enable();
	 
	vector<Matrix4f> Transforms;
               
    float RunningTime = GetRunningTime();

	tow.Model3D.BoneTransform(RunningTime, Transforms);
        
        for (uint i = 0 ; i < Transforms.size() ; i++) {
            m_pEffect->SetBoneTransform(i, Transforms[i]);
        }
		*/

	tow->CalcAnimation();

	m_pEffect->SetEyeWorldPos(Vector3f(cam.eyex,cam.eyey,cam.eyez));

	p.Scale(5,5,5);
	p.Rotate(0,90,-90);
	p.WorldPos(100,50,100);
	m_pEffect->SetWVP(p.GetWVPTrans());
	tow->Render();

	//tow.Model3D.Render();

	//light->Enable();


	static int pathIndex = 0;
	//p.Scale(0.1f, 0.1f, 0.1f);
	float x = path->pathPoints[pathIndex].first;
	float z = path->pathPoints[pathIndex].second;
	float y = terrain->GetTerrainHeight(x, z);
	//p.Rotate(path->GetRotation(Vector3f(x,y,z),pathIndex));

	//p.WorldPos(x,y+1.0,z);
	//light->SetWVP(p.GetWVPTrans());
	//object->Render();

	en.UpdatePosition(&p);

	tow->Shoot(&p,x,y,z);

	/*static float v = 0;
	v += 0.005;
	if(v > 1)
		v = 0;
	float x_dist = x - tow.missilePos.x;
	float y_dist = y -  tow.missilePos.y;
	float z_dist = z -  tow.missilePos.z;

	p.WorldPos(v*x_dist+tow.missilePos.x,v*y_dist+tow.missilePos.y,v*z_dist+tow.missilePos.z);
	p.Scale(5,5,5);
	p.Rotate(0,0,0);
	light->SetWVP(p.GetWVPTrans());
	tow.Missile.Render();
	tow.missileLife += 30;*/
	//tow.Render();





	p.Scale(1, 1, 1);
	p.WorldPos(256, 80, 256);
	p.Rotate(0, 0, 0);
	light->SetWVP(p.GetWVPTrans());
	//object->Render();					//ten wielki nad map¹

	if (++pathIndex >= path->pathPoints.size() - 1)				//obiekt dotar³ do celu 
		pathIndex = 0;

	/*p.Scale(0.5f, 0.5f, 0.5f);
	p.WorldPos(0.0f,-90.0f,0.0f);
	light->SetWVP(p.GetWVPTrans());*/
	
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
	gluPerspective(90.0f, aspect, 0.1f, 1000.0f);		//kat widzenia, aspect ratio, zNear, zFar
	//glOrtho(-1000, 1000, -1000, 1000, -1000, 1000);
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
	double movementSpeed = 150.0;
	cam.STEP_SCALE = 10;

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


	if (!light->Init()) {
            printf("Error initializing the lighting technique\n");
            return -1;
        }

	 m_pEffect = new SkinningTechnique();

        if (!m_pEffect->Init()) {
            printf("Error initializing the lighting technique\n");
            return false;
        }





	light->Enable();
	//camInit();


	m_pEffect->Enable();


	//tow = Tower(light,m_pEffect);
	
	/*tow.light = light;
	tow.m_pEffect = m_pEffect;
	tow.LoadModel("Models/firstTower.md5mesh");
	tow.LoadMissile("Models/missile.fbx");
	tow.missilePos = Vector3f(100,55,100);*/

	tow = new Tower(light,m_pEffect);
	tow->LoadModel("Models/firstTower.md5mesh");
	tow->LoadMissile("Models/missile.fbx");

	//tow.LoadMissile("Models/phoenix_ugv.md2");


	light->Enable();
	if( object->LoadMesh("Models/phoenix_ugv.md2") )
	{
		cout << "udalo sie wczytac" << endl;
	}

	terrain = new Terrain();
	terrain->Init("Models/terrain1.bmp", 0.15f);

	path = new Path(terrain);
	path->Init("Models/path1.bmp");

	en.light = light;
	en.LoadModel("Models/phoenix_ugv.md2");
	en.terrain = terrain;
	en.path = path;

	glutTimerFunc(0, timer, 0);


	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();

	delete object;

	return 0;
}
