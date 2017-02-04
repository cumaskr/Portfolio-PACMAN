#pragma once
#define TILESIZE 30
#define TILEX 40
#define TILEY 20
#define TILESIZEX (TILEX * TILESIZE)
#define TILESIZEY (TILEY * TILESIZE)

#define SAMPLETILEX 20
#define SAMPLETILEY 10







enum CTRL
{
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_BACK,
	CTRL_TERRAINDRAW,
	CTRL_ERASER,
	CTRL_MOUSE,
};

//지형
enum TERRAIN
{
	TR_LOAD,
	TR_WALL,
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
	int x, y;
};

//현재타일 구조체
struct tagCurrentTiles
{
	int x, y;
};