
#include "MapTile.h"
#include "GrafixD2.h"

UINT MapTile::width = 0;
UINT MapTile::height = 0;

MapTile::MapTile(const float2& p )
	:
	CollidableObject(),
	pos(p)
	{
		center = float2(p.x + (float)width / 2, p.y + (float)height / 2);
	}

void MapTile::SetWidthHeight(UINT w, UINT h)
{
	width = w;
	height = h;
}
UINT MapTile::GetIndexXBiasRight(float x)
{
	return (UINT)x / width;
}
UINT MapTile::GetIndexXBiasLeft(float x)
{
	UINT ix = (UINT)x / width;
	if ((float)(ix * width) == x)
		ix--;

	return ix;
}
UINT MapTile::GetIndexYBiasBottom(float y)
{
	return (UINT)y / height;
}
UINT MapTile::GetIndexYBiasTop(float y)
{
	UINT iy = (UINT)y / height;
	if ((float)(iy * height) == y)
		iy--;

	return iy;
}
RectF MapTile::GetRectIndexed(UINT ix, UINT iy)
{
	return RectF((float)(iy * height), (float)(ix)* width,
		(float)(ix + 1) * width, (float)(iy + 1) * height);
}
RectF MapTile::GetRectScreenPos(float ix, float iy)
{
	return RectF((float)(GetIndexYBiasBottom(iy) * height), (float)(GetIndexXBiasRight(ix)) * width,
		(float)(GetIndexXBiasRight(ix) + 1) * width, (float)(GetIndexYBiasBottom(iy) + 1) * height);
}

D2D1_RECT_F MapTile::GetAABB()
{
	return D2D1::RectF(0);
};
float2  MapTile::GetVelocity()
{
	return float2(0.0f, 0.0f);
};
float2  MapTile::GetPosition()
{
	return float2(0.0f, 0.0f);
};

float  MapTile::GetRadius()
{
	return 0.0f;
};
float  MapTile::GetMass()
{
	return 0.0f;
};
float2 MapTile::GetCenter()
{
	return float2(0.0f, 0.0f);
};

//////////////////////////////////////////////////
MapTile::Drawable::Drawable(MapTile& p)
	:
	parent(p)
{
	matRot = Mat3x2Math::Rotate(parent.angle, parent.center);
	matScale = Mat3x2Math::Scale(parent.scale, parent.center);
	matTrans = Mat3x2Math::Translate(parent.pos);
	D2_MATRIX_IDENTITY(matWorld);
}
void MapTile::Drawable::Translate(const float2& pos)
{
	matTrans = Mat3x2Math::Translate(pos);
}
void MapTile::Drawable::Rasterize(GrafixD2& gfx)
{
	matWorld = matRot * matScale * matTrans;
	
	gfx.GetRT()->SetTransform(matTrans);
	gfx.DrawSprite(
		D2D1::RectF(parent.pos.x, parent.pos.y, parent.pos.x + parent.width, parent.pos.y + parent.height),
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
