#include "Pyramid.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>



Pyramid::Pyramid(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
	float startZ = y;
	float startX = x;
	float startY = y;
}

Pyramid::~Pyramid()
{

}

void Pyramid::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnable(GL_NORMAL_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Pyramid::Update()
{
	_position.z += 0.25f;

	if (_position.x >= 0.0f)
	{
		_position.x += 0.05f;
	}
	else
	{
		_position.x -= 0.05f;
	}

	if (_position.y >= 25.0f)
	{
		_position.y += 0.05f;
	}
	else if (_position.y <= -25.0f)
	{
		_position.y -= 0.05f;
	}

	if (_position.z >= 0.0f)
	{
		_position.z = startZ;
		_position.x = startX;
		_position.y = startY;
	}
}