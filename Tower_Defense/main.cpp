#include <iostream>


#include "Model.h"
#include "Camera.h"
#include "basic_lighting.h"
#include "pipeline.h"
#include "skinning_technique.h"
#include "skinned_mesh.h"

/*Global variables -- temporary*/
int refreshMills = 15;        // refresh interval in milliseconds

long long m_frameTime;
	long long m_startTime;
	int m_frameCount;
        int m_fps;


Camera cam;

Mesh* object; 
Mesh* terain; 

BasicLightingTechnique* light;

DirectionalLight m_directionalLight;


SkinningTechnique* m_pEffect;
SkinnedMesh m_mesh;

void initGL() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);				// Set background color
	glClearDepth(1.0f);									// Set background depth to farthest
	glEnable(GL_DEPTH_TEST);							// Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);								// Set the type of depth-test
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	glEnable( GL_TEXTURE_2D );
	
	 m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
     m_directionalLight.AmbientIntensity = 0.7f;				//sila swiatla globalnego
	 m_directionalLight.DiffuseIntensity = 0.2f;
     m_directionalLight.Direction = Vector3f(1.0f, 0.0, 0.0);
}

float GetRunningTime()
{
    float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)m_startTime) / 1000.0f;
    return RunningTime;
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

		 m_pEffect->Enable();
	 
	vector<Matrix4f> Transforms;
               
    float RunningTime = GetRunningTime();

	 m_mesh.BoneTransform(RunningTime, Transforms);
        
        for (uint i = 0 ; i < Transforms.size() ; i++) {
            m_pEffect->SetBoneTransform(i, Transforms[i]);
        }

		m_pEffect->SetEyeWorldPos(Vector3f(cam.eyex,cam.eyey,cam.eyez));

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
	light->Enable();
    light->SetWVP(p.GetWVPTrans());
	 const Matrix4f& WorldTransformation = p.GetWorldTrans();
      light->SetWorldMatrix(WorldTransformation);
      light->SetDirectionalLight(m_directionalLight);

	object->Render();
	//p.Scale(0.1f, 0.1f, 0.1f);
	p.Rotate(0.0f,0.0f, 0.0f);
	p.WorldPos(0.0f,-5.0f,10.0f);
	light->SetWVP(p.GetWVPTrans());
	object->Render();
/*
	p.Scale(0.5f, 0.5f, 0.5f);
	p.WorldPos(0.0f,-90.0f,0.0f);
	light->SetWVP(p.GetWVPTrans())*/;
	//terain->Render();
	 m_pEffect->Enable();
	 Vector3f Pos(Vector3f(0.0f, 0.0f, 2.0f));
        p.WorldPos(Pos);        
        p.Rotate(270.0f, 180.0f, 0.0f);       
        m_pEffect->SetWVP(p.GetWVPTrans());
        m_pEffect->SetWorldMatrix(p.GetWorldTrans());          
	
	 m_mesh.Render();


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
	double movementSpeed = 0.5;

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



	 m_pEffect = new SkinningTechnique();

        if (!m_pEffect->Init()) {
            printf("Error initializing the lighting technique\n");
            return false;
        }

    m_pEffect->Enable();

	if( m_mesh.LoadMesh("Models/boblampclean.md5mesh") )
	{
		cout << "udalo sie wczytac" << endl;
	}


	if( object->LoadMesh("Models/phoenix_ugv.md2") )
	{
		cout << "udalo sie wczytac" << endl;
	}

	glutTimerFunc(0, timer, 0);

	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();

	delete object;

	return 0;
}
