#pragma once


#include "RenderTarget.h"
#include "Vec2.h"

class Camera : public RenderTarget
{
public:// next = vp
	Camera(RenderTarget& next, float width, float height);
	virtual void Rasterize(Drawable& obj);
	float2 GetPos(); 
	void ConfineToMap(RectF& map_frame);
	void Resize(float& w, float& h);
	void UpdatePosition(float2 in_pos);
	bool PointInViewFrame(float2 pt,const float2& offset);
	
private:
	RenderTarget& next;
	float2 pos;
	float2 center;
	RectF mapFrame;
	RectF viewFrame;
	float screen_width, screen_height;
};