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
	{}
	virtual void Rasterize(Drawable& obj)
	{
		
		
		obj.Transform(Mat3x2Math::Translate(-pos));
		next.Rasterize(obj);
		
	}
	void ConfineToRect(RectF& b) { Box = b; };
	void Resize(float& w, float& h)
	{
		screen_width = w;
		screen_height = h;
		center = Vec2F(w / 2, h / 2);
	};
	void UpdatePosition(float2 in_pos)
	{
		pos = in_pos - center;
		pos.x = __max(pos.x, Box.left);
		pos.y = __max(pos.y, Box.top);
		pos.x = __min(pos.x, Box.right - screen_width);
		pos.y = __min(pos.y, Box.bottom - screen_height);
	}
private:
	RenderTarget& next;
	float2 pos;
	float2 center;
	RectF Box;
	float screen_width, screen_height;
};