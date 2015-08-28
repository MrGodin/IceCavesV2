
#include "TileMap.h"
#include "GrafixD2.h"

std::vector<MapTile*>TileMap::tiles;
UINT TileMap::uCols;
UINT TileMap::uRows;
TileMap::_DrawIndex TileMap::drawIndexes;
TileMap::TileMap(Camera& cam, ID2D1Bitmap* bmp, GameLevelData& level_data)
	:
	camera(cam),
	image(bmp),
	levelData(level_data)
{
	uCols = levelData.map_width / levelData.map_tileWidth;
	uRows = levelData.map_height /  levelData.map_tileHeight;
}
//============================================================================
TileMap::~TileMap() 
{
	std::for_each(tiles.begin(), tiles.end(), delete_ptr<MapTile>);
}
MapTile* TileMap::GetTile(int ix, int iy)
{
	UINT result = (UINT)iy  * uCols + (UINT)ix;
	if (result < 0)return NULL;
	return tiles[result];
}
void TileMap::Create(const float2& startPt)
{
	RECT r;
	r.left   = (long)startPt.x;
	r.top    = (long)startPt.y;
	r.right  = r.left + (long)MapTile::GetWidth();
	r.bottom = r.top + (long)MapTile::GetHeight();
	MapTile* tile = nullptr;
	for (UINT y = 0; y < uRows; y++)
	{
		r.left = 0;
		for (UINT x = 0; x < uCols; x++)
		{
			const int index = y * uCols + x;

			EnTileType tType = ttPassable;
			int image_row = 8;
			
			tile = new MapTile(float2((float)r.left,(float)r.top));
			
			tile->SetTileIndex(index);
			tile->SetTexture(image);
			r.left += (long)MapTile::GetWidth();
			r.right = r.left + (long)MapTile::GetWidth();


			switch (levelData.mapStr[index])
			{
			case '1':
			case '2':
			case '3':
			case '4':
			case 'A':
			{
				tile->AddType(ttPassable);
				tile->AddType(ttPrize);
				tile->SetImageIndex(29);
				
				break;
			}
			case 'X':
			{
				tile->AddType(ttPassable);
				tile->AddType(ttPrize);
				tile->SetImageIndex(19);
			}
			break;
			case '?':
			{
				tile->AddType(ttPassable);
				tile->AddType(ttPrize);
				tile->SetImageIndex(16 + 4);
				
				break;
			}
			case 'P':
			{
				tile->AddType(ttPrize);
				tile->SetImageIndex(19);
				
			}break;
			case 'Q':
				tile->AddType(ttSolid);
				tile->SetImageIndex(7 + image_row);
				break;

			case 'S':
				tile->AddType(ttSolid);
				tile->AddType(ttDiffuse);
				tile->SetImageIndex(5 + image_row);
				tile->AddType(ttIrregular);
				break;

			case 'C':
				tile->AddType(ttSolid);
				tile->SetImageIndex(0 + image_row);
				break;
			case 'R':
				tile->AddType(ttSolid);
				tile->SetImageIndex(2 + image_row);
				break;
			case 'L':
				tile->AddType(ttSolid);
				tile->SetImageIndex(1 + image_row);
				break;
			case 'Z':
				tile->AddType(ttSolid);
				tile->SetImageIndex(6 + image_row);
				break;
			case 'W':
				tile->AddType(ttSolid);
				tile->SetImageIndex(3 + image_row);
				break;
			case 'B':
				tile->AddType(ttSolid);
				tile->SetImageIndex(4 + image_row);
				break;
			case ' ':
				tile->AddType(ttSpace);
				tile->SetImageIndex(63);
				break;
			default:
				break;

			}
			UINT image_index = tile->GetImageIndex();
			tile->SetD2ClipRect(grid.GetD2ClipRect((float)image_index));
			tiles.push_back(tile);
		}
		r.top += MapTile::GetHeight();
		r.bottom = r.top + MapTile::GetHeight();
		
	}

	
}
//===================================================================
void TileMap::SetDrawIndex(float2 cam_pos, UINT width, UINT height)
{
	// apparently there is a unsigned int sign issue, so insure positive value
	uint2 cpos = { (UINT)abs(cam_pos.x),(UINT)abs(cam_pos.y) };
	UINT newX = cpos.x + width;
	UINT newY = cpos.y + height;
	UINT w = MapTile::GetWidth();
	UINT h = MapTile::GetHeight();
	drawIndexes.startX = (cpos.x / w);
	drawIndexes.startY = (cpos.y / h);
	drawIndexes.endX   = (newX / w)  + 1;
	drawIndexes.endY   = (newY / h) + 1;
	if (drawIndexes.endY > uRows)drawIndexes.endY = uRows;
	if (drawIndexes.endX > uCols)drawIndexes.endX = uCols;
	
}
void TileMap::CreateImageGrid(UINT width, UINT height, UINT clipsize)
{
	grid.Create((float)width, (float)height, (float)clipsize);
}

////////////////////////////////////////////////////////////////////////////////
//Drawable
////////////////////////////////////////////////////////////////////////////////
TileMap::Drawable::Drawable(TileMap& p)
	:
	parent(p)
{
	
}
void TileMap::Drawable::Translate(const float2& pos)
{
	matTrans = Mat3x2Math::Translate(pos);
}
void TileMap::Drawable::Rasterize(GrafixD2& gfx)
{
	
	for (UINT y = parent.drawIndexes.startY; y < parent.drawIndexes.endY; y++)
	{

		for (UINT x = parent.drawIndexes.startX; x < parent.drawIndexes.endX; x++)
		{
			const UINT index = y * uCols + x;
			parent.camera.Rasterize(tiles[index]->GetDrawable());
		}

	}
	
	

}
/////////////////////////////////////////////////////////////////