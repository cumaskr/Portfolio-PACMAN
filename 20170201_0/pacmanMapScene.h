#pragma once
#include "gameNode.h"
#include "pacmanMapNode.h"
class pacmanMapScene : public gameNode
{
private:
	tagTiles tile[TILEY][TILEX];
	tagSampleTiles sampleTile[SAMPLETILEY][SAMPLETILEX];
	tagCurrentTiles currentTile;

	RECT _rc[4];
	RECT _camera;
	int _cameraX, _cameraY;

	CTRL mouse;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void check();

	void MaptoolSet();
	void Map();
	void MapRender();
	void cameraMove();
	void save();
	void load();

	TERRAIN terrainSelect(int frameX, int frameY);

	pacmanMapScene() {}
	~pacmanMapScene() {}
};

