#include "stdafx.h"
#include "pacmanMapScene.h"

HRESULT pacmanMapScene::init(void)
{
	IMAGEMANAGER->addFrameImage("pacmanMap", "pacmanMap1.bmp", 600, 300, 20, 10);
	_sampleImg = IMAGEMANAGER->findImage("pacmanMap");
	IMAGEMANAGER->findImage("pacmanMap")->setX(600);
	_sampleImg->setY(0);


	MaptoolSet();
	buttoninit();

	mouse = CTRL_TERRAINDRAW;
	_count = 0;
	_sampleCameraX1 = 0;
	_sampleCameraY1 = 0;
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
	if (PtInRect(&_rc[0], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		mouse = CTRL_SAVE;
		save();
	}
	if (PtInRect(&_rc[1], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		mouse = CTRL_LOAD;
		load();
	}
	if (PtInRect(&_rc[2], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		mouse = CTRL_BACK;
		SCENEMANAGER->changeScene("메인메뉴");

	}
	if (PtInRect(&_rc[3], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		mouse = CTRL_TERRAINDRAW;
	}
	if (PtInRect(&_rc[4], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		mouse = CTRL_MOUSE;
		//buttonClick();
	}

	if (mouse == CTRL_MOUSE)
	{
		buttonClick();
	}

	if (PtInRect(&_button[1].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_button[1].isClick = true;
		for (int i = 0; i < 5; i++)
		{
			if (i != 1)
			{
				_button[i].isClick = false;
			}
		}
	}

	if (PtInRect(&_button[2].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_button[2].isClick = true;
		for (int i = 0; i < 5; i++)
		{
			if (i != 2)
			{
				_button[i].isClick = false;
			}
		}
	}
	cameraMove();
	//buttonClick();

}

void pacmanMapScene::render(void)
{
	buttonRender();

	RECT temp;
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			if (_button[1].isClick == true)
			{
				_sampleImg->render(getMemDC(), _sampleImg->getX(), _sampleImg->getY());
			}
		}
	}

	MapRender();

	for (int i = 0; i < 5; i++)
	{
		RectangleMake(getMemDC(), _rc[i]);
	}
	TextOut(getMemDC(), _rc[0].left + 10, _rc[0].top + 10, "SAVE", strlen("SAVE"));
	TextOut(getMemDC(), _rc[1].left + 10, _rc[1].top + 10, "LOAD", strlen("LOAD"));
	TextOut(getMemDC(), _rc[2].left + 10, _rc[2].top + 10, "BACK", strlen("BACK"));
	TextOut(getMemDC(), _rc[3].left + 10, _rc[3].top + 10, "TERRAIN", strlen("TERRAIN"));
	TextOut(getMemDC(), _rc[4].left + 10, _rc[4].top + 10, "MOUSE", strlen("MOUSE"));


	//check();
}

void pacmanMapScene::check()
{
	char str[256];
	sprintf(str, "%d", _button[1].isClick);
	TextOut(getMemDC(), 10, 10, str, strlen(str));
}

void pacmanMapScene::MaptoolSet()
{
	_rc[0] = RectMake(640, 520, 70, 50);
	_rc[1] = RectMake(760, 520, 70, 50);
	_rc[2] = RectMake(880, 520, 70, 50);
	_rc[3] = RectMake(1120, 520, 70, 50);
	_rc[4] = RectMake(1000, 520, 70, 50);

	_camera = RectMake(0, 0, 550, 600);
	_cameraX = 0;
	_cameraY = 0;
	_sampleCamera = RectMake(640, 0, WINSIZEX, 390);
	_sampleCameraX = 640;
	_sampleCameraY = 0;

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			tile[i][j].x = j*TILESIZE;
			tile[i][j].y = i *TILESIZE;
			tile[i][j].rc = RectMake(tile[i][j].x, tile[i][j].y, TILESIZE, TILESIZE);
			tile[i][j].terrainFrameX = 0;
			tile[i][j].terrainFrameY = 10;
			tile[i][j].terrain = terrainSelect(tile[i][j].terrainFrameX, tile[i][j].terrainFrameY);
		}
	}

	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			sampleTile[i][j].terrainFrameX = j;
			sampleTile[i][j].terrainFrameY = i;
			sampleTile[i][j].x = 600 + j*TILESIZE;
			sampleTile[i][j].y = i*TILESIZE;
			sampleTile[i][j].rc = RectMake(sampleTile[i][j].x, sampleTile[i][j].y, TILESIZE, TILESIZE);
		}
	}

}

void pacmanMapScene::buttoninit()
{
	_button[0].x = 580;
	_button[0].y = 0;
	_button[0].rc = RectMake(_button[0].x, _button[0].y, 20, 30);

	_button[1].x = 580;
	_button[1].y = 40;
	_button[1].rc = RectMake(_button[1].x, _button[1].y, 20, 50);

	_button[2].x = 580;
	_button[2].y = 110;
	_button[2].rc = RectMake(_button[2].x, _button[2].y, 20, 50);

	_button[3].x = 580;
	_button[3].y = 180;
	_button[3].rc = RectMake(_button[3].x, _button[3].y, 20, 50);


	_button[4].x = 580;
	_button[4].y = 250;
	_button[4].rc = RectMake(_button[4].x, _button[4].y, 20, 50);

	for (int i = 0; i < 5; i++)
	{
		if (i != 1)
		{
			_button[i].isClick = false;
		}
		if (i == 1)
		{
			_button[i].isClick = true;
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

void pacmanMapScene::buttonClick()
{
	if (PtInRect(&_button[0].rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_button[0].isClick == false)
		{
			_button[0].isClick = true;
			return;
		}
		if (_button[0].isClick == true)
		{
			_button[0].isClick = false;
			return;
		}
	}





	if (_button[0].isClick == true)
	{
		_button[0].x = 1180;
		_button[1].x = 1180;
		_button[2].x = 1180;
		_button[3].x = 1180;
		_button[4].x = 1180;
		_sampleImg->setX(WINSIZEX);
		for (int i = 0; i < SAMPLETILEY; i++)
		{
			for (int j = 0; j < SAMPLETILEX; j++)
			{
				sampleTile[i][j].x = WINSIZEX *TILESIZE;
				sampleTile[i][j].y = i*TILESIZE;
				sampleTile[i][j].rc = RectMake(sampleTile[i][j].x, sampleTile[i][j].y, TILESIZE, TILESIZE);
			}
		}
		_camera = RectMake(0, 0, 1100, 600);
		for (int i = 0; i < 5; i++)
		{
			_rc[i] = RectMake(WINSIZEX, 420, 70, 50);
		}
	}
	if (_button[0].isClick == false)
	{
		buttoninit();
		_sampleImg->setX(600);
		for (int i = 0; i < SAMPLETILEY; i++)
		{
			for (int j = 0; j < SAMPLETILEX; j++)
			{
				sampleTile[i][j].x = 600 + j*TILESIZE;
				sampleTile[i][j].y = i*TILESIZE;
				sampleTile[i][j].rc = RectMake(sampleTile[i][j].x, sampleTile[i][j].y, TILESIZE, TILESIZE);
			}
		}
		_camera = RectMake(0, 0, 550, 600);
		_rc[0] = RectMake(640, 520, 70, 50);
		_rc[1] = RectMake(760, 520, 70, 50);
		_rc[2] = RectMake(880, 520, 70, 50);
		_rc[3] = RectMake(1120, 520, 70, 50);
		_rc[4] = RectMake(1000, 520, 70, 50);
	}

	for (int i = 0; i < 5; i++)
	{
		if (i != 0)
		{
			_button[i].rc = RectMake(_button[i].x, _button[i].y, 20, 50);
		}
		if (i == 0)
		{
			_button[i].rc = RectMake(_button[i].x, _button[i].y, 20, 30);
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
			if (mouse == CTRL_TERRAINDRAW)
			{
				IMAGEMANAGER->frameAlphaRender("pacmanMap", getMemDC(), _ptMouse.x, _ptMouse.y, currentTile.x, currentTile.y, 10);
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
				if (IntersectRect(&temp, &_sampleCamera, &sampleTile[i][j].rc))
				{
					RectangleMake(getMemDC(), sampleTile[i][j].rc);
				}
			}
		}
	}



}

void pacmanMapScene::buttonRender()
{
	//for (int i = 0; i < 5; i++)
	//{
	//	RectangleMake(getMemDC(), _button[i].rc);
	//}
	//TextOut(getMemDC(), _button[0].rc.left + 5, _button[0].rc.top + 5, "X", strlen("X"));
	//TextOut(getMemDC(), _button[1].rc.left + 5, _button[1].rc.top + 5, "1", strlen("1"));
	//TextOut(getMemDC(), _button[2].rc.left + 5, _button[2].rc.top + 5, "2", strlen("2"));
	//TextOut(getMemDC(), _button[3].rc.left + 5, _button[3].rc.top + 5, "3", strlen("3"));
	//TextOut(getMemDC(), _button[4].rc.left + 5, _button[4].rc.top + 5, "4", strlen("4"));

	IMAGEMANAGER->findImage("maptooMenu")->render(getMemDC(), _button[0].rc.left + 3, _button[0].rc.top);
	IMAGEMANAGER->findImage("ChangeSampleImgMenu")->render(getMemDC(), _button[1].rc.left + 3, _button[1].rc.top);
	IMAGEMANAGER->findImage("ChangeSampleImgMenu2")->render(getMemDC(), _button[2].rc.left + 3, _button[2].rc.top);
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
				if (_cameraX <= 506400)
				{
					tile[i][j].x--;
				}
				if (_cameraX > 506400)
				{
					_cameraX = 506400;
				}
			}
		}
	}


	//if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	//{
	//	_sampleCameraX--;
	//	if (_sampleCameraX >= 640)
	//	{
	//		IMAGEMANAGER->findImage("pacmanMap")->setX(IMAGEMANAGER->findImage("pacmanMap")->getX() + 3);
	//	}
	//	for (int i = 0; i < 5; i++)
	//	{
	//		if (_sampleCameraX >= 640)
	//		{
	//			_button[i].x+=3;
	//		}
	//		if (i == 0)
	//		{
	//			_button[i].rc = RectMake(_button[i].x, _button[i].y, 40, 30);
	//		}
	//		if (i != 0)
	//		{
	//			_button[i].rc = RectMake(_button[i].x, _button[i].y, 40, 60);
	//		}
	//	}
	//	for (int i = 0; i < SAMPLETILEY; i++)
	//	{
	//		for (int j = 0; j < SAMPLETILEX; j++)
	//		{
	//			//_sampleCameraX1;
	//			if (_sampleCameraX >= 640)
	//			{
	//				sampleTile[i][j].x+=3;
	//			}
	//			sampleTile[i][j].rc = RectMake(sampleTile[i][j].x, sampleTile[i][j].y, TILESIZE, TILESIZE);
	//		}
	//	}
	//	if (_sampleCameraX < 640)
	//	{
	//		_sampleCameraX = 640;
	//	}
	//
	//}
	//
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	//{
	//	_sampleCameraX++;
	//	if (_sampleCameraX <= 720)
	//	{
	//		IMAGEMANAGER->findImage("pacmanMap")->setX(IMAGEMANAGER->findImage("pacmanMap")->getX() - 3);
	//	}
	//
	//	for (int i = 0; i < 5; i++)
	//	{
	//		if (_sampleCameraX <= 720)
	//		{
	//			_button[i].x -= 3;
	//		}
	//		if (i == 0)
	//		{
	//			_button[i].rc = RectMake(_button[i].x, _button[i].y, 40, 30);
	//		}
	//		if (i != 0)
	//		{
	//			_button[i].rc = RectMake(_button[i].x, _button[i].y, 40, 60);
	//		}
	//	}
	//
	//	for (int i = 0; i < SAMPLETILEY; i++)
	//	{
	//		for (int j = 0; j < SAMPLETILEX; j++)
	//		{
	//			if (_sampleCameraX <= 720)
	//			{
	//				sampleTile[i][j].x-=3;
	//			}
	//			sampleTile[i][j].rc = RectMake(sampleTile[i][j].x, sampleTile[i][j].y, TILESIZE, TILESIZE);
	//		
	//		}
	//	}
	//	if (_sampleCameraX > 720)
	//	{
	//		_sampleCameraX = 720;
	//	}
	//}
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
	if (frameX == 0 && frameY == 10)
	{
		return TR_LOAD;
	}

	else if (frameX == 1 && frameY == 10)
	{
		return TR_LOAD;
	}

	else if (frameX == 2 && frameY == 10)
	{
		return TR_LOAD;
	}

	else if (frameX == 3 && frameY == 10)
	{
		return TR_LOAD;
	}

	else if (frameX == 4 && frameY == 10)
	{
		return TR_LOAD;
	}

	else if (frameX == 5 && frameY == 10)
	{
		return TR_LOAD;
	}

	else if (frameX == 6 && frameY == 10)
	{
		return TR_LOAD;
	}

	else if (frameX == 7 && frameY == 10)
	{
		return TR_LOAD;
	}

	else
	{
		return TR_WALL;
	}

	return TR_LOAD;
}
