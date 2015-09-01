#pragma once

#include "UtilsD2.h"
#include "rect.h"
class Drawable
{

public:
	Drawable()

	{
		clip = { -FLT_MAX, FLT_MAX - 100, -FLT_MAX, FLT_MAX - 100 };

		D2_MATRIX_IDENTITY(matRot);
		D2_MATRIX_IDENTITY(matScale);
		D2_MATRIX_IDENTITY(matTrans);
		D2_MATRIX_IDENTITY(matWorld);
		
	}
	virtual void Rasterize(class GrafixD2& gfx) = 0;
	virtual void Translate(const float2& pos) = 0;
	virtual void Transform(D2D1::Matrix3x2F mat) = 0;
	void Clip( RectF& r)
	{
		clip.ClipTo(r);
	}
protected:
	static D2D1::Matrix3x2F matViewPort;
	D2D1::Matrix3x2F matRot;
	D2D1::Matrix3x2F matScale;
	D2D1::Matrix3x2F matTrans;
	D2D1::Matrix3x2F matWorld;
	RectF clip;
public:
	static void SetViewPort(float2& pos) { matViewPort = D2D1::Matrix3x2F::Translation({ pos.x,pos.y }); }

};