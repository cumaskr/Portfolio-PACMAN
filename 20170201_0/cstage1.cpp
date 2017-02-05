#include "stdafx.h"
#include "cstage1.h"

HRESULT cstage1::init(void)
{
	//IMAGEMANAGER->addFrameImage("pacmanMap", "pacmanMap1.bmp", 600, 390, 20, 13);
	_map = new pacmanMapTool;
	_map->init();

	_enemy = new cEnemy();
	_enemy->GetMap(_map);
	_enemy->init(4, 4);

	return S_OK;
}

void cstage1::release(void)
{
	_map->release();
	SAFE_DELETE(_map);

	_enemy->release();
	SAFE_DELETE(_enemy);
}

void cstage1::update(void)
{
	_map->update();
	_enemy->update();
}

void cstage1::render(void)
{
	_map->render();
	_enemy->render();
}
