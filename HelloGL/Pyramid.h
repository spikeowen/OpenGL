#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class Pyramid : public SceneObject
{
private:
	Vector3 _position;
	float startZ;
	float startX;
	float startY;

public:
	Pyramid(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Pyramid();

	void Draw();
	void Update();
};