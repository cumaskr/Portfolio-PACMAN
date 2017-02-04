#include "stdafx.h"
#include "cstage1.h"

HRESULT cstage1::init(void)
{
	//IMAGEMANAGER->addFrameImage("pacmanMap", "pacmanMap1.bmp", 600, 390, 20, 13);
	_map = new pacmanMapTool;
	_map->init();
	return S_OK;
	return S_OK;
}

void cstage1::release(void)
{
	_map->release();
	SAFE_DELETE(_map);
}

void cstage1::update(void)
{
	_map->update();
}

void cstage1::render(void)
{
	_map->render();
}
