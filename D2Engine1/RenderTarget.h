#pragma once

#include "Drawable.h"
class RenderTarget
{
public:
	virtual void Rasterize(Drawable& obj) = 0;
};