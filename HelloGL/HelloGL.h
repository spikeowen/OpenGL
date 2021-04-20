#pragma once
#include <Windows.h> //Needed for OpenGl on Windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> // OpenGL Utilities
#include "GL\freeglut.h" //freeglut Library
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#include "Pyramid.h"
#include "MeshLoader.h"

#define REFRESHRATE 16

class HelloGL
{
public:
		//Constructor
		HelloGL(int argc, char* argv[]);

		//Destructor
		~HelloGL(void);

		//Display method
		void Display();

		void Update();

		void Keyboard(unsigned char key, int x, int y);

		void InitObjects();

		void InitGL(int argc, char* argv[]);

		void Lights();

		void DrawString(const char* text, Vector3* position, Color* color);

private:
	Camera* camera;
	//Cube* cube[200];
	SceneObject* objects[1000];
	Vector4* _lightPosition;
	Lighting* _lightData;
};
