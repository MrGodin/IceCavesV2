#pragma once

#include "windows.h"

#define MAX_LEVEL_STRINGSIZE 1024 * 5

class _DeltaTime
{
private:
	__int64 cntsPerSec = 0;
	__int64 prevTimeStamp = 0;
	float secsPerCnt = 0.0f;
	__int64 currTimeStamp = 0;

public:
	_DeltaTime() {}
	void start()
	{

		QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
		secsPerCnt = 1.0f / (float)cntsPerSec;
		QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);
	};
	float deltaTime()
	{

		QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
		float dt = (currTimeStamp - prevTimeStamp)*secsPerCnt;
		prevTimeStamp = currTimeStamp;
		return dt;
	}
};

enum EnTileType
{
	ttPassable = 0,
	ttSolid,
	ttPrize,
	ttGamePiece,
	ttSpace,
	ttDiffuse,
	ttIrregular,

	ttNumbTypes,
	ttNone
};
struct TileTypeContainer
{
private:
	EnTileType Types[(int)ttNumbTypes];
protected:
	bool IsType(EnTileType type)
	{
		for (int c = 0; c < (int)ttNumbTypes; c++)
		{
			if (type == Types[c])
				return true;
		}
		return false;
	}
public:
	TileTypeContainer()
	{
		for (int c = 0; c < (int)ttNumbTypes; c++)
			Types[c] = ttNone;
	}
	~TileTypeContainer() {};

	bool Contains(EnTileType type)
	{
		return IsType(type);
	}
	void Add(EnTileType type)
	{
		if (!IsType(type))
		{
			for (int c = 0; c < (int)ttNumbTypes; c++)
			{
				if (Types[c] == ttNone)
				{
					Types[c] = type;
					break;
				}
			}
		}
	};
	void Remove(EnTileType type)
	{

		for (int c = 0; c < (int)ttNumbTypes; c++)
		{
			if (Types[c] == type)
			{
				Types[c] = ttNone;

			}
		}
	}
	void Flush()
	{
		for (int c = 0; c < (int)ttNumbTypes; c++)
			Types[c] = ttNone;
	}
};

struct GameLevelData
{
	char mapStr[MAX_LEVEL_STRINGSIZE];
	UINT map_width;
	UINT map_height;
	UINT map_tileHeight;
	UINT map_tileWidth;
	GameLevelData()
	{
		sprintf_s(mapStr, "%s", "\0");
	}
};