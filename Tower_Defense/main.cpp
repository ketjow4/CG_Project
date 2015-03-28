#include <iostream>


#include "Model.h"
#include "Camera.h"
#include "basic_lighting.h"
#include "pipeline.h"


/*Global variables -- temporary*/
GLfloat anglePyramid = 0.0f;  // Rotational angle for pyramid 
GLfloat angleCube = 0.0f;     // Rotational angle for cube
int refreshMills = 15;        // refresh interval in milliseconds

#define TEST



Camera cam;

Mesh* object; 

BasicLightingTechnique* light;



void initGL() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);				// Set background color
	glClearDepth(1.0f);									// Set background depth to farthest
	glEnable(GL_DEPTH_TEST);							// Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);								// Set the type of depth-test
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	glEnable( GL_TEXTURE_2D );
	

	// 	glEnable( GL_COLOR_MATERIAL );
 //   glColorMaterial( GL_FRONT, GL_AMBIENT );
	////glDisable(GL_BLEND);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_ALPHA_TEST);
 //   glAlphaFunc(GL_NOTEQUAL, 0);
   //glEnable(GL_LIGHT0);

}

Vector3f m_up = Vector3f(0,1,0);
float m_AngleV;

void camInit()
{
	Vector3f HTarget(cam.centerx, 0.0, cam.centerz);
    HTarget.Normalize();
    
    if (HTarget.z >= 0.0f)
    {
        if (HTarget.x >= 0.0f)
        {
            cam.yawAngle = 360.0f - ToDegree(asin(HTarget.z));
        }
        else
        {
            cam.yawAngle = 180.0f + ToDegree(asin(HTarget.z));
        }
    }
    else
    {
        if (HTarget.x >= 0.0f)
        {
            cam.yawAngle = ToDegree(asin(-HTarget.z));
        }
        else
        {
            cam.yawAngle = 90.0f + ToDegree(asin(-HTarget.z));
        }
    }
    
	m_AngleV = -ToDegree(asin(cam.centery));
}


void camUpdate()
{
	const Vector3f Vaxis(0.0f, 1.0f, 0.0f);

    // Rotate the view vector by the horizontal angle around the vertical axis
    Vector3f View(1.0f, 0.0f, 0.0f);
	View.Rotate(cam.yawAngle, Vaxis);
    View.Normalize();

    // Rotate the view vector by the vertical angle around the horizontal axis
    Vector3f Haxis = Vaxis.Cross(View);
    Haxis.Normalize();
	View.Rotate(45, Haxis);
       
	View.Normalize();

	cam.centerx = View.x;
	cam.centery = View.y;
	cam.centerz = View.z;

	m_up = View.Normalize().Cross(Haxis);
    m_up.Normalize();
}

// funkcja generuj¹ca scenê 3D
void Display()
{
	//cam.UpdateCamera();
	camUpdate();
	glDisable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


	//cam.UpdateCamera();		//NEW

	
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
	p.SetCamera(Vector3f(cam.eyex, cam.eyey, cam.eyez ), Vector3f(cam.centerx, cam.centery, cam.centerz), m_up);
	p.SetPerspectiveProj(pers);

	/*glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)glutGet( GLUT_WINDOW_WIDTH )/(float)glutGet( GLUT_WINDOW_HEIGHT ), 0.1f, 1000.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(cam.eyex, cam.eyey, cam.eyez ), glm::vec3(cam.centerx, cam.centery, cam.centerz), glm::vec3(0,1,0));
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0,0,10));
	glm::mat4  projectiont = glm::transpose(projection);
	glm::mat4 viewt = glm::transpose(view);
	glm::mat4 result = projectiont * viewt * glm::transpose(model);*/
	//light->SetWVP(Matrix4f(result[0][0],result[0][1],result[0][2],result[0][3],result[1][0],result[1][1],result[1][2],result[1][3],result[2][0],result[2][1],result[2][2],result[2][3],result[3][0],result[3][1],result[3][2],result[3][3]));
	
	
    light->SetWVP(p.GetWVPTrans());
	object->Render();
	p.Rotate(0.0f,0.0f, 0.0f);
	p.WorldPos(0.0f,-5.0f,10.0f);
	light->SetWVP(p.GetWVPTrans());
	object->Render();


	
	
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
		//cam.eyey -= 0.5;
		cam.Rotate(-angle);	//kat_obrotu += 5;
	}
	if( key == 'x')
	{
		//cam.eyey += 0.5;
		cam.Rotate(angle);	//kat_obrotu -= 5;
	}

	// odrysowanie okna
	Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}

//Dzia³a nie tykaæ
void SpecialKeys( int key, int x, int y )
{
	double movementSpeed = 0.5;
	double STEP_SCALE = 1.0;
	Vector3f Left = Vector3f(cam.centerx,cam.centery,cam.centerz).Cross(Vector3f(0,1,0));
	Vector3f Right = Vector3f(0,1,0).Cross(Vector3f(cam.centerx,cam.centery,cam.centerz));
	
	switch( key )
	{
		// kursor w lewo
	case GLUT_KEY_LEFT:
#ifdef TEST
			Left.Normalize();
			Left *= STEP_SCALE;
			cam.eyex += Left.x;
			cam.eyey += Left.y;
			cam.eyez += Left.z;
#else
			cam.MoveLeft(movementSpeed);
#endif
		break;

		// kursor w górê
	case GLUT_KEY_UP:
		

#ifdef TEST
		cam.eyex += (Vector3f(cam.centerx,cam.centery,cam.centerz) * STEP_SCALE).x;
		//cam.eyey += (Vector3f(cam.centerx,cam.centery,cam.centerz) * STEP_SCALE).y;
		cam.eyez += (Vector3f(cam.centerx,cam.centery,cam.centerz) * STEP_SCALE).z;
#else
		cam.MoveForward(movementSpeed);
#endif
		break;

		// kursor w prawo
	case GLUT_KEY_RIGHT:
#ifdef TEST		            
            Right.Normalize();
            Right *= STEP_SCALE;
            cam.eyex += Right.x;
			cam.eyey += Right.y;
			cam.eyez += Right.z;
#else
		cam.MoveRight(movementSpeed);

#endif
		break;

		// kursor w dó³
	case GLUT_KEY_DOWN:
		#ifdef TEST	
		cam.eyex -= (Vector3f(cam.centerx,cam.centery,cam.centerz) * STEP_SCALE).x;
		//cam.eyey -= (Vector3f(cam.centerx,cam.centery,cam.centerz) * STEP_SCALE).y;
		cam.eyez -= (Vector3f(cam.centerx,cam.centery,cam.centerz) * STEP_SCALE).z;
#else
		cam.MoveBackward(movementSpeed);
#endif
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

	light->Enable();
	camInit();


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
