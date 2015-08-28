#pragma once


#include "RenderTarget.h"
#include "Vec2.h"

class Camera : public RenderTarget
{
public:// next = vp
	Camera(RenderTarget& next, float width, float height);
	virtual void Rasterize(Drawable& obj);
	float2 GetPos(); 
	void ConfineToRect(RectF& b);
	void Resize(float& w, float& h);
	void UpdatePosition(float2 in_pos);
	
private:
	RenderTarget& next;
	float2 pos;
	float2 center;
	RectF Box;
	float screen_width, screen_height;
};