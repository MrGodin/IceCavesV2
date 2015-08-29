#pragma once

#include "Enemy.h"
#include "Player.h"
#include "Camera.h"
#include "ObjContainer.h"


class EnemyContainer : public ObjContainer
{
private:
	Camera& camera;
	
public:
	
	EnemyContainer(Camera& cam);
	
	virtual void Rasterize();
	virtual void Update(CollidableObject& player, float& dt);
	
};