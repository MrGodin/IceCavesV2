#pragma once

#include "CollidableObject.h"
#include "Drawable.h"

class MapTile : public CollidableObject
{
protected:
	static UINT width;
	static UINT height;
	UINT index;
	UINT imageIndex;
	TileTypeContainer enTypes;
	D2D1_RECT_F clipRect;
	float angle;
	D2D1_SIZE_F scale;
	D2D1_SIZE_F t;
	float2 center;
	float2 pos;
	ID2D1Bitmap* pBitmap = nullptr;
	D2D1_BITMAP_PROPERTIES bp;
	D2D1_BITMAP_INTERPOLATION_MODE interpMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
	float transparency = 1.0f;
public:
	MapTile() {}
	MapTile(const float2& p);
	~MapTile() {}
	// Static
		static void SetWidthHeight(UINT w, UINT h);
		static UINT GetIndexXBiasRight(float x);
		static UINT GetIndexXBiasLeft(float x);
		static UINT GetIndexYBiasBottom(float y);
		static UINT GetIndexYBiasTop(float y);
		static RectF GetRectIndexed(UINT ix, UINT iy);
		static RectF GetRectScreenPos(float ix, float iy);
		static UINT GetWidth() { return width; }
		static UINT GetHeight() { return height; }
	//~
	//==================
	// virtuals
		virtual RectF GetAABB()override;
		virtual float2  GetVelocity()override;
		virtual float2  GetPosition()override;
		virtual float  GetRadius()override;
		virtual float  GetMass()override;
		virtual float2 GetCenter()override;
		
	//~
	//========================
	//Tile Types
		bool    IsType(EnTileType type) { return enTypes.Contains(type); }
		bool    Passable() { return enTypes.Contains(ttPassable); }
		bool    Solid() { return enTypes.Contains(ttSolid); }
		bool    Prize() { return enTypes.Contains(ttPrize); }
		bool    GamePiece() { return enTypes.Contains(ttGamePiece); }
		bool    Space() { return enTypes.Contains(ttSpace); }
		bool    Diffuse() { return enTypes.Contains(ttDiffuse); }
		void    AddType(EnTileType type) { enTypes.Add(type); }
		void    RemoveType(EnTileType type) { enTypes.Remove(type); }
		void    FlushTypes() { enTypes.Flush(); }
	//~
	//=======================
		void SetTileIndex(UINT i) { index = i; }
		UINT GetTileIndex() { return index; }
		void SetImageIndex(UINT i) { imageIndex = i; }
		UINT GetImageIndex() { return imageIndex; }
		void SetD2ClipRect(D2D1_RECT_F rect) { clipRect = rect; }
		void SetTexture(ID2D1Bitmap* bmp) { pBitmap = bmp; }
	//====================
	
	class Drawable : public ::Drawable
	{
	public:
		Drawable(MapTile& p);
		virtual void Translate(const float2& pos)override;
		virtual void Rasterize(class GrafixD2& gfx)override;
		virtual void Transform(D2D1::Matrix3x2F mat)override;
	private:
		const MapTile& parent;
	};
	Drawable GetDrawable() { return Drawable(*this); }
};