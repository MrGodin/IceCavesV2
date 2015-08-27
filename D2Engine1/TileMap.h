#pragma once

#include "MapTile.h"
#include "Camera.h"
#include "Drawable.h"
#include "ImageGrid.h"




class TileMap
{
public:
	TileMap(Camera& cam,ID2D1Bitmap* bmp, GameLevelData& level_data );
	~TileMap();
	static MapTile* GetTile(int ix, int iy);
private:
	static std::vector<MapTile*>tiles;
	static UINT uRows;
	static UINT uCols;
	GridF grid;
	Camera& camera;
	ID2D1Bitmap* image = nullptr;
	GameLevelData levelData;
	
	struct _DrawIndex
	{
		UINT startX;
		UINT startY;
		UINT endX;
		UINT endY;
	};
	static _DrawIndex drawIndexes;
	
	
public:
	class Drawable : public ::Drawable
	{
	public:
		Drawable(TileMap& p);
		virtual void Translate(const float2& pos)override;
		virtual void Rasterize(class GrafixD2& gfx)override;
		virtual void Transform(D2D1::Matrix3x2F mat) {}
	private:
		const TileMap& parent;
	};
	Drawable GetDrawable() { return Drawable(*this); }
	void Create( const float2& startPt);
	void CreateImageGrid(UINT width, UINT height, UINT clipsize);
	void  static SetDrawIndex(float2 cam_pos, UINT width, UINT height);
	
};