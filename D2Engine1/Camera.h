#pragma once


#include "RenderTarget.h"
#include "Vec2.h"

class Camera : public RenderTarget
{
public:// next = vp
	Camera(RenderTarget& next, float width, float height)
		:
		next(next),
		pos({ 0,0 }),
		center({ width / 2.0f,height / 2.0f }),
		screen_width(width),
		screen_height(height)
	{
		
	}
	virtual void Rasterize(Drawable& obj)
	{
		
		
		obj.Transform(Mat3x2Math::Translate(-pos));
		next.Rasterize(obj);
		
	}
	float2 GetPos() { return pos; }
	void ConfineToRect(RectF& b) { Box = b; };
	void Resize(float& w, float& h);
	
	void GetScreenSize(float& w, float& h)
	{
		w = screen_width;
		h = screen_height;

	}
	void UpdatePosition(float2 in_pos);
	
private:
	RenderTarget& next;
	float2 pos;
	float2 center;
	RectF Box;
	float screen_width, screen_height;
};