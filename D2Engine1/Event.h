#pragma once

#include "UtilsD2.h"
class EventTimer
{
private:
	float timer = 0.0f;
	float elapsedTime = 0.0f;
	float lifeSpan = 0.0f;
public:
	EventTimer(const float& lifespan);
	void Tick(float& dt);
	void Reset(float& lifespan, float starttime = 0.0f);
	float ElapsedTime() { return elapsedTime; }
	virtual void OnTimer(float& dt, float& elapsed_time,bool& reset) = 0;
};