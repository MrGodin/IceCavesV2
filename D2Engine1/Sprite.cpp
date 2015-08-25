#include "Sprite.h"
#include "UtilsD2.h"

Sprite::Sprite()
	:
	CollidableObject()
{
	
}

Sprite::Sprite( float2 pos,float Width, float Height, ID2D1Bitmap *Bitmap, D2D1_RECT_F clipR)
	:
	CollidableObject(),
	pos(pos),
	width(Width),
	height(Height),
	pBitmap(Bitmap),
	scale({ Width,Height }),
	clipRect(clipR)
{
	
}
Sprite::~Sprite()
{
	
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

/////////////////////////////////////////////////////////////////////

Sprite::Drawable::Drawable(Sprite& p)
	:
	parent(p)
{
	 Transform(Mat3x2Math::Translate(parent.pos));
	D2_MATRIX_IDENTITY(matWorld);
}
void Sprite::Drawable::Translate(const float2& pos)
{
	matTrans = Mat3x2Math::Translate(pos);
}
void Sprite::Drawable::Transform(D2D1::Matrix3x2F mat)
{
	matTrans = mat * matTrans;
}
 void Sprite::Drawable::Rasterize(GrafixD2& gfx)
{
	matWorld =  matRot * matScale * matTrans ;

	gfx.GetRT()->SetTransform(matTrans);
	gfx.DrawSprite(
	    parent.GetDrawSize(),// D2D1::RectF(parent.core.pos.x, parent.core.pos.y, parent.core.pos.x + parent.width, parent.core.pos.y + parent.height),
		parent.pBitmap,
		parent.bp,
		parent.transparency,
		parent.interpMode,
		&parent.clipRect//D2D1::RectF(parent.clipRect.left, parent.clipRect.top, parent.clipRect.right, parent.clipRect.bottom)
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