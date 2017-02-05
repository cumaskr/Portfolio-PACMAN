#include "stdafx.h"
#include "cEnemy.h"
#include "pacmanMapTool.h"

HRESULT cEnemy::init(int _indexX, int _indexY)
{
	tag_Enemy* enemy = new tag_Enemy();
	enemy->indexX = _indexX;
	enemy->indexY = _indexY;
	enemy->x = _map->getTile(enemy->indexX, enemy->indexY).x;
	enemy->y = _map->getTile(enemy->indexX, enemy->indexY).y;
	enemy->rc = RectMake(enemy->x, enemy->y, TILESIZE, TILESIZE);
	vEnemyList.push_back(enemy);

	return S_OK;
}

void cEnemy::release(void)
{
	for (int i = 0; i < vEnemyList.size(); i++)
	{
		SAFE_DELETE(vEnemyList[i]);
	}
	vEnemyList.clear();
}

void cEnemy::update(void)
{
}

void cEnemy::render(void)
{
	for (int i = 0; i < vEnemyList.size(); i++)
	{
		RectangleMake(getMemDC(), vEnemyList[i]->rc);
		TextOut(getMemDC(), vEnemyList[i]->rc.left, vEnemyList[i]->rc.top, TEXT("Àû"), lstrlen(TEXT("Àû")));
	}

}
