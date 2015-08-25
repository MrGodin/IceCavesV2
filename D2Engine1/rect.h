
#pragma once
#pragma once

#include "windows.h"
#include "UtilsD2.h"
#include "Vectors.h"
template <class T>
class _Rect
{
public:
	T top;
	T left;
	T right;
	T bottom;
public:
	_Rect()
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}
	_Rect(T top, T left, T right, T bottom)
		:
		top(top),
		left(left),
		right(right),
		bottom(bottom)
	{}
	_Rect(_Rect& r)
		:
		top(r.top),
		left(r.left),
		right(r.right),
		bottom(r.bottom)
	{}
	
	void SetRectR(RECT r)
	{

		bottom = (T)r.bottom;
		left = (T)r.left;
		right = (T)r.right;
		top = (T)r.top;

	}
	void Translate(T x, T y)
	{

		left += x;
		right += x;
		top += y;
		bottom += y;
	}
	
	D2D1_RECT_F ToD2Rect()
	{
		return D1D2::RectF((float)top,(float)left,(float)right,(float)bottom);
	}
	void ClipTo(_Rect rect)
	{
		left = __max(left, rect.left);
		top = __max(top, rect.top);
		right = __min(right, rect.right);
		bottom = __min(bottom, rect.bottom);
	}
	inline bool OverLaps(_Rect& rect)
	{
		return top < rect.bottom && bottom > rect.top && left < rect.right && right > rect.left;
	}

	inline bool Conatins(Vector2<T>& pt)
	{
		return pt.x >= left && pt.x <= right && pt.y >= top && pt.y <= bottom;
	}
	template <class T2>
	operator _Rect< T2 >() const
	{
		return _Rect<int>((T2)top, (T2)left, (T2)right, (T2)bottom);
	}

	int GetWidth() { return (int)(right - left); }
	int GetHeight() { return (int)(bottom - top); }
};
typedef _Rect< float > RectF;
typedef _Rect< int > RectI;
typedef _Rect< long > RectL;
