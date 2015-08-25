
#pragma once
#include "RenderTarget.h"
#include "UtilsD2.h"
#include "rect.h"

class Viewport : public RenderTarget
{
public:// next = grafix
	Viewport(RenderTarget& next, RectF rect)
		:
		next(next),
		clip(rect)
	{
		
	}
	RectF GetClip() { return clip; }

	virtual void Rasterize(Drawable& obj)
	{
		obj.Transform(Mat3x2Math::Translate(float2((float)clip.left,(float)clip.top)));
		obj.Clip(clip);
		next.Rasterize(obj);
	}
	int GetWidth() { return clip.GetWidth(); }
	int GetHeight() { return clip.GetHeight(); }
	float2 GetPos() { return float2((float)clip.left, (float)clip.top); }
private:
	RenderTarget& next;
	
	RectF clip;
};
