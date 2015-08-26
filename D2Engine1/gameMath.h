#pragma once
#include "Vec2.h"

static const float PI_F = 3.14159265358979323846f;
class Math
{
public:
	template<typename T>
	static __inline T Negate(T val)
	{
		return -val;
	}

	static __inline float RandFloat(float min, float max)
	{
		return (static_cast<float>(rand() % RAND_MAX) / static_cast<float>(RAND_MAX)) * (max - min) + min;
	};

	static __inline float CalculateRadians(float2 velocity)
	{
		float hypothenuse = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
		float sine = velocity.y / hypothenuse;
		float angle = asin(sine);
		return angle;
	};
	static __inline D2D1_RECT_F GetImageRectFromIndex(int index, ID2D1Bitmap* bmp, int clipw, int cliph)
	{
		D2D1_SIZE_F s_wh = bmp->GetSize();
		int framesPerCol = (int)s_wh.width / clipw;
		int framesPerRow = (int)s_wh.height / cliph;
		int row = index / framesPerCol;
		int col = index % framesPerRow;
		float x = (float)(col * clipw);
		float y = (float)(row * clipw);
		return D2D1::RectF(x, y, x + (float)clipw, y + (float)cliph);
	}
	static __inline float CalculateRadiansFromAngle(float angle)
	{
		return angle * PI_F / 180.0f;
	};

	static __inline float ConvertDipsToPixels(float dips, float dpi)
	{
		static const float dipsPerInch = 96.0f;
		return floor(dips * dpi / dipsPerInch + 0.5f);
	};

	

	template <class T>
	static __inline float IsFacing(_Vec2<T> centerA, _Vec2<T> centerB, _Vec2<T> velA, _Vec2<T> velB, float radiusA, float radiusB)
	{
		_Vec2<T> delta = centerA - centerB;
		float d = delta.Len();

		// minimum translation distance to push balls apart after intersecting

		Vec2<T> mtd = delta * (radiusA + radiusB - d) / d;
		// impact speed
		Vec2<T> v = (velA - velB);
		Vec2<T> mtdNorm = mtd.Normalize();// V2Math::norm(mtd);
		float vn = v.x*mtdNorm.x + v.y*mtdNorm.y;
		return sgn(vn) ;
	}


	template <typename T>
	static int sgn(T val)
	{
		return (T(0) < val) - (val < T(0));
	}
};
