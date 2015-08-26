#pragma once

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "windows.h"

// Common Constants

#define PI_F 3.1415927f

// Template Vector & Matrix Classes


template <class T> struct Vector2
{
	union
	{
		struct
		{
			T x;
			T y;
		};
		struct
		{
			T r;
			T g;
		};
		struct
		{
			T u;
			T v;
		};
	};
	Vector2<T> operator += (Vector2<T>rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}
	T& operator[](unsigned int index)
	{
		return static_cast<T*>(this)[index];
	}

	Vector2(T _x = 0, T _y = 0) : x(_x), y(_y) { }
	__inline Vector2&	CW90()
	{
		T temp = y;
		y = x;
		x = -temp;
		return *this;
	}
	inline Vector2&	CCW90()
	{
		T temp = y;
		y = -x;
		x = temp;
		return *this;
	}
};

template <class T> struct Vector3
{
	union
	{
		struct
		{
			T x;
			T y;
			T z;
		};
		struct
		{
			T r;
			T g;
			T b;
		};
		struct
		{
			T u;
			T v;
			T w;
		};
	};

	T& operator[](unsigned int index)
	{
		return static_cast<T*>(this)[index];
	}
	
	Vector3(T _x = 0, T _y = 0, T _z = 0) : x(_x), y(_y), z(_z) { }
};

template <class T> struct Vector4
{
	union
	{
		struct
		{
			T x;
			T y;
			T z;
			T w;
		};
		struct
		{
			T r;
			T g;
			T b;
			T a;
		};
	};

	T& operator[](unsigned int index)
	{
		return static_cast<T*>(this)[index];
	}

	Vector4(T _x = 0, T _y = 0, T _z = 0, T _w = 0) : x(_x), y(_y), z(_z), w(_w) { }
};
typedef unsigned int uint;


typedef Vector3<float> float3;
typedef Vector4<float> float4;
template <class T>
Vector2<T> operator-(Vector2<T> a, Vector2<T> b)
{
	return Vector2<T>(a.x - b.x, a.y - b.y);
}

template <class T>
Vector2<T> operator-(Vector2<T> a)
{
	return Vector2<T>(-a.x, -a.y);
}

template <class T>
Vector3<T> operator-(Vector3<T> a, Vector3<T> b)
{
	return Vector3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template <class T>
Vector3<T> operator-(Vector3<T> a)
{
	return Vector3<T>(-a.x, -a.y, -a.z);
}
template <class T>
bool operator==(Vector3<T> a, Vector3<T> b)
{
	return    a.x == b.x && a.y == b.y && a.z == b.z;
}


template <class T>
Vector4<T> operator-(Vector4<T> a, Vector4<T> b)
{
	return Vector4<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

template <class T>
Vector4<T> operator-(Vector4<T> a)
{
	return Vector4<T>(-a.x, -a.y, -a.z, -a.w);
}

template <class T>
Vector2<T> operator+(Vector2<T> a, Vector2<T> b)
{
	return Vector2<T>(a.x + b.x, a.y + b.y);
}

template <class T>
Vector3<T> operator+(Vector3<T> a, Vector3<T> b)
{
	return Vector3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template <class T>
Vector4<T> operator+(Vector4<T> a, Vector4<T> b)
{
	return Vector4<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

template <class T>
Vector2<T> operator*(Vector2<T> a, T s)
{
	return Vector2<T>(a.x * s, a.y * s);
}

template <class T>
Vector2<T> operator*(T s, Vector2<T> a)
{
	return a * s;
}

template <class T>
Vector2<T> operator*(Vector2<T> a, Vector2<T> b)
{
	return Vector2<T>(a.x * b.x, a.y * b.y);
}

template <class T>
Vector2<T> operator/(Vector2<T> a, T s)
{
	return Vector2<T>(a.x / s, a.y / s);
}

template <class T>
Vector3<T> operator*(Vector3<T> a, T s)
{
	return Vector3<T>(a.x * s, a.y * s, a.z * s);
}

template <class T>
Vector3<T> operator*(T s, Vector3<T> a)
{
	return a * s;
}

template <class T>
Vector3<T> operator*(Vector3<T> a, Vector3<T> b)
{
	return Vector3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
}

template <class T>
Vector3<T> operator/(Vector3<T> a, T s)
{
	return Vector3<T>(a.x / s, a.y / s, a.z / s);
}

template <class T>
Vector4<T> operator*(Vector4<T> a, T s)
{
	return Vector4<T>(a.x * s, a.y * s, a.z * s, a.w * s);
}

template <class T>
Vector4<T> operator*(T s, Vector4<T> a)
{
	return a * s;
}

template <class T>
Vector4<T> operator*(Vector4<T> a, Vector4<T> b)
{
	return Vector4<T>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

template <class T>
Vector4<T> operator/(Vector4<T> a, T s)
{
	return Vector4<T>(a.x / s, a.y / s, a.z / s, a.w / s);
}
// Template Vector Operators
