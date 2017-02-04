#pragma once
#include "gameNode.h"
#include "pacmanMapNode.h"
class pacmanMapTool : public gameNode
{
private:
	tagTiles tile[TILEY][TILEX];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void load();
	tagTiles getTile(int indexX, int indexY) { return tile[indexX][indexY]; }

	pacmanMapTool() {}
	~pacmanMapTool() {}
};

