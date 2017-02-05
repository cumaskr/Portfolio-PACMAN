#pragma once
#include "gameNode.h"

class pacmanMapTool;

struct tag_Enemy
{
	float x;
	float y;
	RECT rc;
	int indexX;
	int indexY;
};


class cEnemy : public gameNode
{
private:
	TCHAR buffer[123];
	pacmanMapTool* _map;
	vector<tag_Enemy*> vEnemyList;

public:

	vector<tag_Enemy*> GetVenemyList() { return vEnemyList; }
	void GetMap(pacmanMapTool* _mmap) { _map = _mmap; }
	HRESULT init(int _indexX, int _indexY);
	void release(void);
	void update(void);
	void render(void);

	cEnemy() {}
	~cEnemy() {}
};

