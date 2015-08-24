#pragma once


#include "RenderTarget.h"
#include "Vectors.h"

class Camera : public RenderTarget
{
public:// next = vp
	Camera(RenderTarget& next, float width, float height)
		:
		next(next),
		pos({ 0,0 }),
		center({ width / 2.0f,height / 2.0f })
	{}
	virtual void Rasterize(Drawable& obj)
	{
		
		obj.Translate(-pos);
		next.Rasterize(obj);
		
	}
	void UpdatePosition(float2 in_pos)
	{
		pos = in_pos - center;
	}
private:
	RenderTarget& next;
	float2 pos;
	float2 center;
};