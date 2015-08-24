#pragma once
#include "GrafixD2.h"
#include "Drawable.h"
#include "Texture.h"
#include "UtilsD2.h"
#include "Colliadable.h"
#include "ObjectState.h"
class Sprite : public CollidableObject
{
public:
	Sprite();
	Sprite(float2 pos,float Width, float Height, ID2D1Bitmap *Bitmap);
	~Sprite();

	//====================================================
	//Collidable Object
	virtual D2D1_RECT_F GetAABB();
	virtual float2  GetVelocity();
	virtual float2  GetPosition() ;
	virtual void   SetVelocity(const float2 v);
	virtual void   SetPosition(const float2 p);
	virtual float  GetRadius();
	virtual float  GetMass();
	virtual float2  GetCenter();
	virtual void   Rebound(const float2 normal);
	virtual  ObjectCore* GetCore();

	void SetProperties(float DpiX, float DpiY, D2D1_PIXEL_FORMAT PixFormat = D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
	void SetInterpolationMode(D2D1_BITMAP_INTERPOLATION_MODE InterpMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	
	
	//=================================================================================
	class Collide : public ::Collide
	{
	public:
		Collide(Sprite& p);
		virtual void SphericalCollision(CollidableObject& obj)override;
		virtual void MapCollision()override;
	private:
		 Sprite& parent;
	};

	//=================================================================================
	class Drawable : public ::Drawable
	{
	public:
		Drawable(Sprite& p);
		virtual void Translate(const float2& pos)override;
		virtual void Rasterize(GrafixD2& gfx)override;
	private:
		const Sprite& parent;
	};
	//=========================================================
	void SetDrawSize() { drawRect.left = core.pos.x; 
	                     drawRect.top = core.pos.y; 
						 drawRect.right = core.pos.x + width; 
						 drawRect.bottom = core.pos.y + height;
	}
	D2D_RECT_F GetDrawSize() { return D2D1::RectF(core.pos.x, core.pos.y, width, height); }
	Drawable GetDrawable() { return Drawable(*this); }
	Collide GetCollision() { return Collide(*this); }
private:
	float width, height;
	D2D1_BITMAP_PROPERTIES bp;
	D2D1_BITMAP_INTERPOLATION_MODE interpMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
	ID2D1Bitmap *pBitmap;
	
	float2 center;
	float angle = 0.0f;
	float transparency = 1.0f;
	D2D_RECT_F clipRect = {0.0f,0.0f,64.0f,64.0f};
	D2D_RECT_F drawRect = { 0.0f,0.0f,64.0f,64.0f };
	D2D1_SIZE_F scale;
	ObjectCore core;
};

