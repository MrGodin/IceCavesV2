#pragma once
#include"Drawable.h"
#include "GrafixD2.h"
class StaticAnimation
{
public:
	struct StaticAnimationDesc
	{
		UINT index;
		UINT frames;
		UINT clipWidth;
		UINT clipHeight;
		float2 clip_startpos;
		float2 pos;
		float life_span;
		ID2D1Bitmap* bmp = nullptr;
		D2D1_BITMAP_PROPERTIES bp;
		D2D1_BITMAP_INTERPOLATION_MODE interpMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
		float transparency = 1.0f;
		D2D1_RECT_F drawPos;
		
	};
private:
	
	
	_EventTimer timer;
	float fElapsedtime = 0.0f;;
	std::vector<D2D1_RECT_F>clipRect;
	
	void createClipRects();

	
	StaticAnimationDesc Desc;
public:
	StaticAnimation(StaticAnimationDesc& desc);
	class Drawable : public ::Drawable
	{
	public:
		Drawable(StaticAnimation& p);
		virtual void Rasterize(class GrafixD2& gfx)override;
		virtual void Translate(const float2& pos)override;
		virtual void Transform(D2D1::Matrix3x2F mat)override;
	private:
		StaticAnimation& parent;
	};
	Drawable GetDrawable() { return Drawable(*this); }
	bool     Update(float& dt);
	
};