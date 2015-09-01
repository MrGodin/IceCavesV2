#pragma once
#include"Drawable.h"
#include "GrafixD2.h"






class StaticAnimation
{
	void createClipRects();
public:
	struct AnimationDesc
	{
		UINT index = 0;
		UINT frames = 1;
		UINT startFrame = 0;
		UINT endFrame = 1;
		UINT clipWidth = 32;
		UINT clipHeight = 32;
		UINT drawWidth = 32;
		UINT drawHeight = 32;
		UINT clipOffsetW = 0;
		UINT clipOffsetH = 0;
		float2 clip_startpos = { 0.0f,0.0f };
		float2 center = { (float)clipWidth / 2.0f,(float)clipHeight / 2.0f };
		float2 pos = { 0.0f,0.0f };
		float angle = 0.0f;
		float life_span = 0.0f;
		ID2D1Bitmap* bmp = nullptr;
		D2D1_BITMAP_PROPERTIES bp;
		D2D1_BITMAP_INTERPOLATION_MODE interpMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
		float transparency = 1.0f;
		D2D1_RECT_F drawPos = D2D1::RectF(0.0f, 0.0f, 32.0f, 32.0f);
		bool keep_alive = true;
		bool do_animate = true;
		
	};
protected:
	_EventTimer timer;
	float fElapsedtime = 0.0f;;
	std::vector<D2D1_RECT_F>clipRect;
	
	AnimationDesc Desc;
public:
	StaticAnimation(AnimationDesc& desc);
	virtual ~StaticAnimation(){}
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
	virtual bool     Update(float& dt);
	void SetIndex(UINT index) { Desc.index = index; }
	void SetStartEndFrame(UINT start, UINT end, float lifespan);
	void AngleInc(float val) { Desc.angle += val; }
};

class MoveableAnimation : public StaticAnimation
{
protected:
	
public:
	MoveableAnimation(AnimationDesc& desc);
	virtual bool Update(float& dt)override;
	void SetPos(float2& pos);
	
	void SetIndex(UINT index) { Desc.index = index;}
	void DoAnimate(bool animate, UINT startIndex = 0) { Desc.do_animate = animate; SetIndex(startIndex); }
	bool Animate() { return Desc.do_animate; }
};