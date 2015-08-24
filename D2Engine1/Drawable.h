#pragma once

#include "UtilsD2.h"
class Drawable
{
public:
	Drawable()
	{
		D2_MATRIX_IDENTITY(matRot);
		D2_MATRIX_IDENTITY(matScale);
		D2_MATRIX_IDENTITY(matTrans);
		D2_MATRIX_IDENTITY(matWorld);
	}
	virtual void Rasterize(class GrafixD2& gfx) = 0;
	virtual void Translate(const float2& pos) = 0;
protected:
	D2D1::Matrix3x2F matRot;
	D2D1::Matrix3x2F matScale;
	D2D1::Matrix3x2F matTrans;
	D2D1::Matrix3x2F matWorld;
};