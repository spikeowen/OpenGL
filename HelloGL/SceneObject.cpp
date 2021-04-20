#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
	_mesh = mesh;
	_texture = texture;
}

SceneObject::~SceneObject()
{
	//make sure to delete _mesh properties here
}

void SceneObject::Update()
{

}
void SceneObject::Draw()
{

}