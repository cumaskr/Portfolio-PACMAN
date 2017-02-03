#pragma once
#define TILESIZE 30
#define TILEX 30
#define TILEY 20
#define TILESIZEX (TILEX * TILESIZE)
#define TILESIZEY (TILEY * TILESIZE)

#define SAMPLETILEX 20
#define SAMPLETILEY 13







enum CTRL
{
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_BACK,
	CTRL_TERRAINDRAW,
	CTRL_ERASER,
};

//지형
enum TERRAIN
{
	TR_CEMENT, TR_GROUND, TR_GRASS, TR_WATER, TR_END
};

struct tagTiles
{
	TERRAIN terrain;
	RECT rc;

	int terrainFrameX;
	int terrainFrameY;
	int x, y;
};

 

struct tagSampleTiles
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
};

//현재타일 구조체
struct tagCurrentTiles
{
	int x, y;
};