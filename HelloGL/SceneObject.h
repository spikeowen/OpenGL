#pragma once
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Mesh* _mesh;
	Texture2D* _texture;

public:
	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject();

	virtual void Update(bool paused);
	virtual void Draw();
	virtual void Rotate(float rotation);
};
