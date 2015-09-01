
#include "Event.h"

EventTimer::EventTimer(const float& lifespan)
	:
	lifeSpan(lifespan)
{

}
void EventTimer::Tick(float& dt)
{
	elapsedTime += dt;
	if ((timer += dt) > lifeSpan)
	{
		bool reSet = false;
		OnTimer(dt, elapsedTime,reSet);
		if (!reSet)
			timer = 0.0f;
	}
}
void EventTimer::Reset(float& lifespan, float starttime)
{
	lifeSpan = lifespan;
	timer = starttime;
	elapsedTime = 0.0f;
}