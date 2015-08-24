#pragma once
#include "windows.h"
#include "d2d1.h"
#include "Vectors.h"

class Mat3x2Math
{
public:
	static D2D1::Matrix3x2F Rotate(float angle, float2 center)
	{
		return D2D1::Matrix3x2F::Rotation(angle,D2D1::Point2F(center.x,center.y));
	}
	static D2D1::Matrix3x2F Scale(const D2D1_SIZE_F& size, const float2& center)
	{
		return D2D1::Matrix3x2F::Scale(size, D2D1::Point2F(center.x, center.y));
	}
	static D2D1::Matrix3x2F Translate(const float2& pos)
	{
		return D2D1::Matrix3x2F::Translation(pos.x,pos.y);
	}
};