#pragma once

#include "Enemy.h"

class EnemyCannon : public Enemy
{
	_EventTimer timer;
	void fireBall();
	float timer_delay;
	bool can_fire;
public:
	EnemyCannon(EnemyDesc& desc,float& delay);
	~EnemyCannon() {}
	virtual void Update(float dt)override;
	void Reset() { timer.Set(timer_delay); }
	bool DoFire() { return can_fire; }
};