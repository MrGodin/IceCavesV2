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
	Sprite(float2 pos,float Width, float Height, ID2D1Bitmap *Bitmap,D2D1_RECT_F clipR);
	virtual ~Sprite();

	//====================================================
	//Collidable Object
	void SetProperties(float DpiX, float DpiY, D2D1_PIXEL_FORMAT PixFormat = D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
	void SetInterpolationMode(D2D1_BITMAP_INTERPOLATION_MODE InterpMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
	void SetTexture(ID2D1Bitmap* bmp) { pBitmap = bmp; }
	void SetD2ClipRect(D2D1_RECT_F r) { clipRect = r; }
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
	class Drawable : public ::Drawable
	{
	public:
		Drawable(Sprite& p);
		virtual void Translate(const float2& pos)override;
		virtual void Rasterize(GrafixD2& gfx)override;
		virtual void Transform(D2D1::Matrix3x2F mat)override;
	private:
		 Sprite& parent;
	};
	//=========================================================
	
	virtual D2D_RECT_F GetDrawSize() = 0;
	virtual void Update(float dt) {}
	Drawable GetDrawable() { return Drawable(*this); }
	Collide GetCollision() { return Collide(*this); }
private:
	
	D2D1_BITMAP_PROPERTIES bp;
	D2D1_BITMAP_INTERPOLATION_MODE interpMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
	ID2D1Bitmap *pBitmap;
	UINT imageIndex;
	
protected:
	float width, height;
	float2 center;
	float2 pos;
	float angle = 0.0f;
	float transparency = 3.0f;
	D2D_RECT_F clipRect = {0.0f,0.0f,64.0f,64.0f};
	D2D_RECT_F drawRect = { 0.0f,0.0f,64.0f,64.0f };
	D2D1_SIZE_F scale;

	
};

