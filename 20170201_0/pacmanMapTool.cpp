#include "stdafx.h"
#include "pacmanMapTool.h"


HRESULT pacmanMapTool::init(void)
{
	load();
	return S_OK;
}

void pacmanMapTool::release(void)
{
}

void pacmanMapTool::update(void)
{
}

void pacmanMapTool::render(void)
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			IMAGEMANAGER->frameRender("pacmanMap", getMemDC(), tile[i][j].rc.left, tile[i][j].rc.top, tile[i][j].terrainFrameX, tile[i][j].terrainFrameY);
		}
	}
}

void pacmanMapTool::load()
{

	HANDLE file;
	DWORD read;

	file = CreateFile("stage1.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, tile, sizeof(tagTiles) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);

}
