#pragma once
#include "GrafixD2.h"
#include "Drawable.h"
#include "Texture.h"
#include "UtilsD2.h"
#include "Colliadable.h"
#include "ObjectState.h"
#include "Animation.h"

class Sprite : public CollidableObject
{
public:
	struct SpriteDesc
	{
		float width, height;
		StaticAnimation::AnimationDesc animateDesc;
		
	};
public:
	//Sprite();
	Sprite(SpriteDesc& desc)
	:Desc(desc),
	animation(Desc.animateDesc)
	{
		width = Desc.width;
		height = Desc.height;
		
	}
	
	virtual ~Sprite();
	virtual float GetHitPts() = 0;
	virtual void SetHitPts(const float& val) = 0;
	virtual void SetHitPtsInc(const float& val) = 0;
	//====================================================
	//Collidable Object
	void SetProperties(float DpiX, float DpiY, D2D1_PIXEL_FORMAT PixFormat = D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
	void SetInterpolationMode(D2D1_BITMAP_INTERPOLATION_MODE InterpMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	void SetTexture(ID2D1Bitmap* bmp) { Desc.animateDesc.bmp = bmp; }
	void SetImageIndex(UINT index) { animation.SetIndex(index); }
	void SetAnimationSequence(UINT start, UINT end, float lifespan)
	{
		animation.SetStartEndFrame(start, end,lifespan);
	}
	
	
	//=================================================================================
	class Collide : public ::Collide
	{
	public:
		Collide(Sprite& p);
		virtual bool SphericalCollision(CollidableObject& obj)override;
		virtual void MapCollision()override;
	private:
		 Sprite& parent;
	};

	//=================================================================================
	
	//=========================================================
	
	virtual D2D_RECT_F GetDrawSize() = 0;
	virtual void Update(float dt) {}
	StaticAnimation::Drawable GetDrawable() { return animation.GetDrawable(); }
	Collide GetCollision() { return Collide(*this); }
private:
	
	
	
protected:
	SpriteDesc Desc;
	float width, height;
	
	MoveableAnimation animation;
	
};

