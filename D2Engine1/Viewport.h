
#pragma once
#include "RenderTarget.h"
#include "UtilsD2.h"
#include "rect.h"

class Viewport : public RenderTarget
{
public:// next = grafix
	Viewport(RenderTarget& next, RectI rect)
		:
		next(next),
		clip(rect)
	{
		
	}
	RectI GetClip() { return clip; }

	virtual void Rasterize(Drawable& obj)
	{
		next.Rasterize(obj);
	}
	int GetWidth() { return clip.GetWidth(); }
	int GetHeight() { return clip.GetHeight(); }
private:
	RenderTarget& next;
	
	RectI clip;
};
