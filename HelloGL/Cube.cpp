#include "Cube.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>



Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	_rotation = rand() % 100;
	speeds = 1.0f / (rand() % 5 + 1.0f);
	//rnd = floor + int((range * rand()) / (RAND_MAX + 1.0));
	_position.x = x;
	_position.y = y;
	_position.z = z;
	startZ = _position.z;
}

Cube::~Cube()
{

}

void Cube::Draw()
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

		Materials();
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(_material->Diffuse.x));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(_material->Specular.x));
		glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);
		glRotatef(_rotation * 2.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(_rotation / 2.0f, 0.0f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Cube::Update()
{
	_rotation += speeds;
	_position.z += 0.25f;
	if (_position.z >= 0.0f)
	{
		_position.z = startZ;
	}
}

void Cube::Materials()
{
	_material = new Material();
	_material->Ambient.x = 0.6; 
	_material->Ambient.y = 0.6; 
	_material->Ambient.z = 0.8;
	_material->Ambient.w = 1.0;

	_material->Diffuse.x = 0.6; 
	_material->Diffuse.y = 0.6;
	_material->Diffuse.z = 0.8;
	_material->Diffuse.w = 1.0;

	_material->Specular.x = 1.0; 
	_material->Specular.y = 1.0; 
	_material->Specular.z = 1.0;
	_material->Specular.w = 1.0;

	_material->Shininess = 100.0f;
}