#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class Cube : public SceneObject
{
private:
	GLfloat _rotation;
	float speeds;
	float startZ;
	float startX;
	float startY;
	Vector3 _position;
	Material* _material;

	void Materials();

	//int floor = 1, ceiling = 3.5, range = (ceiling - floor);
	//int rnd;

	

public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw();
	void Update(bool paused);
	void Rotate(float rotation);
};