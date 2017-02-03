#include "stdafx.h"
#include "pacmanMapScene.h"

HRESULT pacmanMapScene::init(void)
{
	IMAGEMANAGER->addFrameImage("pacmanMap", "pacmanMap1.bmp", 600, 390, SAMPLETILEX, SAMPLETILEY);

	MaptoolSet();

	mouse = CTRL_TERRAINDRAW;
	return S_OK;
}

void pacmanMapScene::release(void)
{
}

void pacmanMapScene::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		Map();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rc[0], _ptMouse))
		{
			mouse = CTRL_SAVE;
			save();
		}

		if (PtInRect(&_rc[1], _ptMouse))
		{
			mouse = CTRL_LOAD;
			load();
		}

		if (PtInRect(&_rc[2], _ptMouse))
		{
			mouse = CTRL_BACK;
			SCENEMANAGER->changeScene("메인메뉴");
		}

		if (PtInRect(&_rc[3], _ptMouse))
		{
			mouse = CTRL_TERRAINDRAW;
		}
	}

	cameraMove();
}

void pacmanMapScene::render(void)
{

	IMAGEMANAGER->render("pacmanMap", getMemDC(), 400, 0);

	MapRender();


	for (int i = 0; i < 4; i++)
	{
		RectangleMake(getMemDC(), _rc[i]);
	}
	TextOut(getMemDC(), _rc[0].left + 10, _rc[0].top + 10, "SAVE", strlen("SAVE"));
	TextOut(getMemDC(), _rc[1].left + 10, _rc[1].top + 10, "LOAD", strlen("LOAD"));
	TextOut(getMemDC(), _rc[2].left + 10, _rc[2].top + 10, "BACK", strlen("BACK"));
	TextOut(getMemDC(), _rc[3].left + 10, _rc[3].top + 10, "TERRAIN", strlen("TERRAIN"));

	//check();
}

void pacmanMapScene::check()
{
	char str[256];
	sprintf(str, "%d", _cameraX);
	TextOut(getMemDC(), 10, 10, str, strlen(str));
}

void pacmanMapScene::MaptoolSet()
{
	_rc[0] = RectMake(400, 500, 100, 50);
	_rc[1] = RectMake(550, 500, 100, 50);
	_rc[2] = RectMake(700, 500, 100, 50);
	_rc[3] = RectMake(850, 500, 100, 50);

	_camera = RectMake(0, 0, 360, 600);
	_cameraX = 0;
	_cameraY = 0;

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			tile[i][j].x = j*TILESIZE;
			tile[i][j].y = i *TILESIZE;
			tile[i][j].rc = RectMake(tile[i][j].x, tile[i][j].y, TILESIZE, TILESIZE);
			tile[i][j].terrainFrameX = 0;
			tile[i][j].terrainFrameY = 0;
			tile[i][j].terrain = terrainSelect(tile[i][j].terrainFrameX, tile[i][j].terrainFrameY);
		}
	}

	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			sampleTile[i][j].terrainFrameX = j;
			sampleTile[i][j].terrainFrameY = i;
			sampleTile[i][j].rc = RectMake(400 + j*TILESIZE, i*TILESIZE, TILESIZE, TILESIZE);
		}
	}

}

void pacmanMapScene::Map()
{
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			if (PtInRect(&sampleTile[i][j].rc, _ptMouse))
			{
				currentTile.x = sampleTile[i][j].terrainFrameX;
				currentTile.y = sampleTile[i][j].terrainFrameY;
			}
		}
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (PtInRect(&tile[i][j].rc, _ptMouse))
			{
				if (mouse == CTRL_TERRAINDRAW && PtInRect(&_camera, _ptMouse))
				{
					tile[i][j].terrainFrameX = currentTile.x;
					tile[i][j].terrainFrameY = currentTile.y;
					tile[i][j].terrain = terrainSelect(currentTile.x, currentTile.y);
				}
			}
		}
	}

}

void pacmanMapScene::MapRender()
{
	RECT temp;
	//전체화면 왼쪽에 지형을 그린다
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (IntersectRect(&temp, &_camera, &tile[i][j].rc))
			{
				IMAGEMANAGER->frameRender("pacmanMap", getMemDC(), tile[i][j].rc.left, tile[i][j].rc.top, tile[i][j].terrainFrameX, tile[i][j].terrainFrameY);
			}
		}
	}

	if (KEYMANAGER->isToggleKey(VK_F10))
	{
		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				if (IntersectRect(&temp, &_camera, &tile[i][j].rc))
				{
					RectangleMake(getMemDC(), tile[i][j].rc);
				}
			}
		}
	}
	if (KEYMANAGER->isToggleKey(VK_F11))
	{
		for (int i = 0; i < SAMPLETILEY; i++)
		{
			for (int j = 0; j < SAMPLETILEX; j++)
			{
				RectangleMake(getMemDC(), sampleTile[i][j].rc);
			}
		}
	}



}

void pacmanMapScene::cameraMove()
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				tile[i][j].rc = RectMake(tile[i][j].x, tile[i][j].y, TILESIZE, TILESIZE);
				_cameraX--;
				if (_cameraX >= 0)
				{
					tile[i][j].x++;
				}
				if (_cameraX < 0)
				{
					_cameraX = 0;
				}
			}
		}

	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				tile[i][j].rc = RectMake(tile[i][j].x, tile[i][j].y, TILESIZE, TILESIZE);
				_cameraX++;
				if (_cameraX <= 307800)
				{
					tile[i][j].x--;
				}
				if (_cameraX > 307800)
				{
					_cameraX = 307800;
				}
			}
		}
	}
}

void pacmanMapScene::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, tile, sizeof(tagTiles) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);
}

void pacmanMapScene::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, tile, sizeof(tagTiles) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}

TERRAIN pacmanMapScene::terrainSelect(int frameX, int frameY)
{
	if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}
	if (frameX == 2 && frameY == 0)
	{
		return TR_GROUND;
	}
	if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}
	if (frameX == 4 && frameY == 0)
	{
		return TR_WATER;
	}

	return TR_GROUND;
}
