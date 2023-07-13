#include "HelloGL.h"
#include <time.h>

HelloGL::HelloGL(int argc, char* argv[])
{
	srand(time(NULL));

	InitGL(argc, argv);
	InitObjects();
	Lights();
	pause = false;
	
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
	delete camera;
	for (int i = 0; i < 500; i++)
	{
		delete objects[i];
	}
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //this clears the scene
	for (int i = 0; i < 500; i++)
	{
		objects[i]->Draw();
	}
	Vector3 v = { -1.4f, 0.7f, -1.0f };
	Color c = { 1.0f, 1.0f, 1.0f };
	DrawString("Meteor Storm Demo By Spike Owen", &v, &c);
	glFlush(); //flushes the scene drawn to the graphics card
	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity();
	for (int i = 0; i < 500; i++)
	{
		objects[i]->Update(pause);
	}
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
	{
		camera->eye.x -= 0.1f;
	}

	if (key == 'a')
	{
		camera->eye.x += 0.1f;
	}

	if (key == 'w')
	{
		camera->eye.y -= 0.1f;
	}

	if (key == 's')
	{
		camera->eye.y += 0.1f;
	}

	if (key == 'p' && pause == false)
	{
		pause = true;
	}
	else if (key == 'p' && pause == true)
	{
		pause = false;
	}

	if (key == 'q' && pause == true)
	{
		for (int i = 0; i < 500; i++)
		{
			objects[i]->Rotate(1.0f);
		}
	}
}

void HelloGL::InitObjects()
{
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");

	BMPReader* tempText = new BMPReader();
	tempText->loadBitMap((char*)"Asteroid.bmp", (char*)"Asteroid.raw");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Asteroid.raw", 512, 512);

	Texture2D* texture2 = new Texture2D();
	texture2->Load((char*)"stars.raw", 512, 512);
	
	camera = new Camera();

	for (int i = 0; i < 500; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % (1000-100 + 1) + 100) / 10.0f);
	}
	//for (int i = 500; i < 1000; i++)
	//{
	//	objects[i] = new Pyramid(pyramidMesh, texture2, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	//}

	//old
	camera->eye.x = 0.0f;
	camera->eye.y = 0.0f;
	camera->eye.z = 1.0f;

	//Cube viewer
	/*camera->eye.x = 5.0f;
	camera->eye.y = 5.0f;
	camera->eye.z = -5.0f;*/

	camera->center.x = 0.0f;
	camera->center.y = 0.0f;
	camera->center.z = 0.0f;

	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Spike's OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Set viewport to be whole window
	glViewport(0, 0, 800, 800);
	//Set perspective
	gluPerspective(45, 1, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void HelloGL::Lights()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2;
	_lightData->Ambient.y = 0.2;
	_lightData->Ambient.z = 0.2;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glPushMatrix();
	glTranslatef(position->x + 0.6f, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
}