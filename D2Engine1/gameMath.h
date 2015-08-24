#pragma once
#include "Vectors.h"
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

	inline float CalculateRadians(float2 velocity)
	{
		float hypothenuse = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
		float sine = velocity.y / hypothenuse;
		float angle = asin(sine);
		return angle;
	};

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
	static __inline float IsFacing(Vector2<T> centerA, Vector2<T> centerB, Vector2<T> velA, Vector2<T> velB, float radiusA, float radiusB)
	{
		Vector2<T> delta = centerA - centerB;
		float d = V2Math::len(delta);

		// minimum translation distance to push balls apart after intersecting

		Vector2<T> mtd = delta * (radiusA + radiusB - d) / d;
		// impact speed
		Vector2<T> v = (velA - velB);
		Vector2<T> mtdNorm = V2Math::norm(mtd);
		float vn = v.x*mtdNorm.x + v.y*mtdNorm.y;
		return vn ;
	}


	template <typename T>
	static int sgn(T val)
	{
		return (T(0) < val) - (val < T(0));
	}
};
class V2Math
{
public:
	template <class T>
	static float len(Vector2<T> a)
	{
		return sqrt(pow(a.x, 2.0f) + pow(a.y, 2.0f));
	}
	template <class T>
	static __inline float dot(Vector2<T> a, Vector2<T> b)
	{
		return  a.x * b.x + a.y * b.y;
	}
	template <class T>
	static Vector2<T> normCW(Vector2<T> a)
	{
		float _len = len(a);
		return Vector2<T>(a.x / _len, a.y / _len).CW90();
	}
	template <class T>
	static Vector2<T> normCCW(Vector2<T> a)
	{
		float _len = len(a);
		return Vector2<T>(a.x / _len, a.y / _len).CCW90();
	}
	template <class T>
	static Vector2<T> norm(Vector2<T> a)
	{
		float _len = len(a);
		return Vector2<T>(a.x / _len, a.y / _len);
	}
	template <class T>
	static Vector2<T> LineNormCW(Vector2<T> a, Vector2<T> b)
	{
		Vector2<T> result = a - b;
		return normCW(result);
		
	}
	template <class T>
	static Vector2<T> LineNormCCW(Vector2<T> a, Vector2<T> b)
	{
		Vector2<T> result = a - b;
		return normCCW(result);

	}
	template <class T>
	static float dist(Vector2<T> a, Vector2<T> b)
	{
		return sqrt(pow(a.x - b.x, 2) + pow(b.y - b.y, 2));
	}
	template <class T>
	static __inline Vector2<T>	MidPointOnLine( Vector2<T> p1, Vector2<T> p2) 
	{
		float dx = (p1.x + p2.x) / 2.0f;
		float dy = (p1.y + p2.y) / 2.0f;
		return Vector2<T>(dx, dy);
	}

	/*if we define dx = x2 - x1 and dy = y2 - y1, then the normals are(-dy, dx) and (dy, -dx).
	inline <class T>	CrossWith(const float2 &rhs) const
	{
		return x * rhs.y - y * rhs.x;
	}*/
	
};