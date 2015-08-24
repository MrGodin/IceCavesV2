#include "Sprite.h"
#include "UtilsD2.h"

Sprite::Sprite()
	:
	CollidableObject()
{
	ZeroMemory(&core, sizeof(ObjectCore));
}

Sprite::Sprite( float2 pos,float Width, float Height, ID2D1Bitmap *Bitmap)
	:
	CollidableObject(),
	width(Width),
	height(Height),
	pBitmap(Bitmap),
	scale({ Width,Height })
{
	ZeroMemory(&core, sizeof(ObjectCore));
	core.pos = pos;
}
Sprite::~Sprite()
{
	SAFE_RELEASE(pBitmap);
	SAFE_DELETE(core.state);
}


void Sprite::SetProperties(float DpiX, float DpiY, D2D1_PIXEL_FORMAT PixFormat)
{
	bp.dpiX = DpiX;
	bp.dpiY = DpiY;
	bp.pixelFormat = PixFormat;
	
	
}

void Sprite::SetInterpolationMode(D2D1_BITMAP_INTERPOLATION_MODE InterpMode)
{
	interpMode = InterpMode;
}
D2D1_RECT_F Sprite::GetAABB()
{
	return D2D1::RectF(core.pos.x,core.pos.y,core.pos.x+width,core.pos.y+height);
};
float2  Sprite::GetVelocity()
{
	return core.vel;
};
float2  Sprite::GetPosition()
{
	return core.pos;
};
void   Sprite::SetVelocity(const float2 v)
{
	core.vel = v;
};
void   Sprite::SetPosition(const float2 p)
{
	core.pos = p;
};
float  Sprite::GetRadius()
{
	return __max(width * 0.5f, height * 0.5f);
};
float  Sprite::GetMass()
{
	return core.mass;
};
float2  Sprite::GetCenter()
{
	return float2(core.pos.x + (width * 0.5f),core.pos.y + (height * 0.5f));
};
void   Sprite::Rebound(const float2 normal)
{};
ObjectCore* Sprite::GetCore()
{
	return &core;
};
/////////////////////////////////////////////////////////////////////

Sprite::Drawable::Drawable(Sprite& p)
	:
	parent(p)
{
	matRot = Mat3x2Math::Rotate(parent.angle, parent.center);
	matScale = Mat3x2Math::Scale(parent.scale, parent.center);
	matTrans = Mat3x2Math::Translate(parent.core.pos);
	D2_MATRIX_IDENTITY(matWorld);
}
void Sprite::Drawable::Translate(const float2& pos)
{
	matTrans = Mat3x2Math::Translate(pos);
}
 void Sprite::Drawable::Rasterize(GrafixD2& gfx)
{
	matWorld = matRot * matScale * matTrans;

	gfx.GetRT()->SetTransform(matWorld);
	gfx.DrawSprite(
		D2D1::RectF(parent.core.pos.x, parent.core.pos.y, parent.core.pos.x + parent.width, parent.core.pos.y + parent.height),
		parent.pBitmap,
		parent.bp,
		parent.transparency,
		parent.interpMode,
		&D2D1::RectF(parent.clipRect.left, parent.clipRect.top, parent.clipRect.right, parent.clipRect.bottom)
		);
	//reset transform so we have no carry-over to next sprite
	gfx.GetRT()->SetTransform(D2D1::Matrix3x2F::Identity());
}
/////////////////////////////////////////////////////////////////
Sprite::Collide::Collide(Sprite& p)
	:
	parent(p)
{

};
void Sprite::Collide::SphericalCollision(CollidableObject& obj)
{
	Collision::HandleSphericalObjectCollision(parent, obj);
}
void Sprite::Collide::MapCollision()
{
	Collision::HandleMapCollision(parent);
}