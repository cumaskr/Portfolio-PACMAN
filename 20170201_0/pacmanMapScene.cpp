#include "stdafx.h"
#include "pacmanMapScene.h"

HRESULT pacmanMapScene::init(void)
{
	IMAGEMANAGER->addFrameImage("pacmanMap", "pacmanMap1.bmp", 600, 300, 20, 10);
	_sampleImg = IMAGEMANAGER->findImage("pacmanMap");
	IMAGEMANAGER->findImage("pacmanMap")->setX(600);
	_sampleImg->setY(0);


	MaptoolSet();				//맵툴 초기화
	buttoninit();				//위쪽 버튼 초기화

	mouse = CTRL_TERRAINDRAW;	//현재 마우스 상태
	_sampleCameraX1 = 0;		//필요없음	
	_sampleCameraY1 = 0;		//필요없음	

	anyInit();					//애니메이션 초기화
	return S_OK;
}

void pacmanMapScene::release(void)
{
}

void pacmanMapScene::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		Map();		//맵에 타일들 배치가능
	}
	if (PtInRect(&_rc[0], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		mouse = CTRL_SAVE; //마우스상태, 세이브
		save();
	}
	if (PtInRect(&_rc[1], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		mouse = CTRL_LOAD;	//마우스상태, 로드
		load();
	}
	if (PtInRect(&_rc[2], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		mouse = CTRL_BACK;  //마우스상태, 돌아가기
		SCENEMANAGER->changeScene("메인메뉴");

	}
	if (PtInRect(&_rc[3], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		mouse = CTRL_TERRAINDRAW;   //마우스상태
	}
	if (PtInRect(&_rc[4], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		mouse = CTRL_MOUSE;     //마우스상태
	}

	if (mouse == CTRL_MOUSE)
	{
		buttonClick();    //위쪽버튼 활성화
	}
	cameraMove();	//사실 카메라는 고정임
	anyTime();		//애니메이션 돌아간다
}

void pacmanMapScene::render(void)
{
	buttonRender();	//위쪽버튼 렌더
	anyRender();	//애니메이션 렌더
	RECT temp;
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			if (_button[1].isClick == true)
			{
				//옆에 샘플타일 1스테이지니까 위에 1을 누르면 이아이가 그려짐
				_sampleImg->render(getMemDC(), _sampleImg->getX(), _sampleImg->getY());
			}
		}
	}

	MapRender();	//게임화면 맵 렌더

					//for (int i = 0; i < 5; i++)
					//{
					//	RectangleMake(getMemDC(), _rc[i]);
					//}
					//TextOut(getMemDC(), _rc[0].left + 10, _rc[0].top + 10, "SAVE", strlen("SAVE"));
					//TextOut(getMemDC(), _rc[1].left + 10, _rc[1].top + 10, "LOAD", strlen("LOAD"));
					//TextOut(getMemDC(), _rc[2].left + 10, _rc[2].top + 10, "BACK", strlen("BACK"));
					//TextOut(getMemDC(), _rc[3].left + 10, _rc[3].top + 10, "TERRAIN", strlen("TERRAIN"));
					//TextOut(getMemDC(), _rc[4].left + 10, _rc[4].top + 10, "MOUSE", strlen("MOUSE"));
					//밑에 버튼 활성화 렌더임 
	if (PtInRect(&_rc[0], _ptMouse))
	{
		IMAGEMANAGER->findImage("saveBig")->render(getMemDC(), _rc[0].left - 10, _rc[0].top - 10);
	}

	if (PtInRect(&_rc[1], _ptMouse))
	{
		IMAGEMANAGER->findImage("loadBig")->render(getMemDC(), _rc[1].left - 10, _rc[1].top - 10);
	}

	if (PtInRect(&_rc[2], _ptMouse))
	{
		IMAGEMANAGER->findImage("backBig")->render(getMemDC(), _rc[2].left - 10, _rc[2].top - 10);
	}

	if (PtInRect(&_rc[3], _ptMouse))
	{
		IMAGEMANAGER->findImage("drawBig")->render(getMemDC(), _rc[3].left - 30, _rc[3].top - 10);
	}

	if (PtInRect(&_rc[4], _ptMouse))
	{
		IMAGEMANAGER->findImage("mapBig")->render(getMemDC(), _rc[4].left - 20, _rc[4].top - 10);
	}

	if (!PtInRect(&_rc[0], _ptMouse))
	{
		IMAGEMANAGER->findImage("save")->render(getMemDC(), _rc[0].left, _rc[0].top);
	}

	if (!PtInRect(&_rc[1], _ptMouse))
	{
		IMAGEMANAGER->findImage("load")->render(getMemDC(), _rc[1].left, _rc[1].top);
	}

	if (!PtInRect(&_rc[2], _ptMouse))
	{
		IMAGEMANAGER->findImage("back")->render(getMemDC(), _rc[2].left, _rc[2].top);
	}

	if (!PtInRect(&_rc[3], _ptMouse))
	{
		IMAGEMANAGER->findImage("draw")->render(getMemDC(), _rc[3].left - 10, _rc[3].top);
	}

	if (!PtInRect(&_rc[4], _ptMouse))
	{
		IMAGEMANAGER->findImage("map")->render(getMemDC(), _rc[4].left, _rc[4].top);
	}

	//check();
}

void pacmanMapScene::check()
{
	char str[256];
	sprintf(str, "%d", _button[1].isClick);
	TextOut(getMemDC(), 10, 10, str, strlen(str));
}

void pacmanMapScene::anyInit()
{
	_isAnyLeft = false;
	_count = 0;

	_any[0].x = 550;
	_any[0].y = 400;
	_any[0].frameX = 0;
	_any[0].frameY = 0;
	_any[0].img = IMAGEMANAGER->findImage("maptoolPacmanAny");

	_any[1].x = _any[0].x - 100;
	_any[1].y = 400;
	_any[1].frameX = 0;
	_any[1].frameY = 0;
	_any[1].img = IMAGEMANAGER->findImage("maptoolEnemyAny0");

	_any[2].x = _any[1].x - 39;
	_any[2].y = 400;
	_any[2].frameX = 0;
	_any[2].frameY = 0;
	_any[2].img = IMAGEMANAGER->findImage("maptoolEnemyAny1");

	_any[3].x = _any[2].x - 39;
	_any[3].y = 400;
	_any[3].frameX = 0;
	_any[3].frameY = 0;
	_any[3].img = IMAGEMANAGER->findImage("maptoolEnemyAny2");

	_any[4].x = _any[3].x - 39;
	_any[4].y = 400;
	_any[4].frameX = 0;
	_any[4].frameY = 0;
	_any[4].img = IMAGEMANAGER->findImage("maptoolEnemyAny3");


	_any[5].x = _any[4].x - 39;
	_any[5].y = 400;
	_any[5].frameX = 0;
	_any[5].frameY = 0;
	_any[5].img = IMAGEMANAGER->findImage("maptoolEnemyAny4");

}

void pacmanMapScene::anyTime()
{
	_count++;
	if (_count > 100)
	{
		_count = 0;
	}
	for (int i = 0; i < 6; i++)
	{
		//오른쪽 끝으로 가면 다시 돌아옴 
		if (_isAnyLeft == false)
		{
			_any[i].x += 4;
			_any[i].frameY = 0;
			if (_count % 3 == 0)
			{
				_any[i].frameX++;
				if (i != 0)
				{
					if (_any[i].frameX > 2)
					{
						_any[i].frameX = 0;
					}
				}

				if (i == 0)
				{
					if (_any[i].frameX > 3)
					{
						_any[i].frameX = 0;
					}
				}
			}
			if (_any[5].x - 50 > WINSIZEX)
			{
				_isAnyLeft = true;
				break;
			}

		}
		//왼쪽 게임맵 조금 지나면 다시 돌아간다
		if (_isAnyLeft == true)
		{
			_any[i].x -= 4;
			_any[i].frameY = 1;
			if (_count % 3 == 0)
			{
				_any[i].frameX++;
				if (i != 0)
				{
					if (_any[i].frameX > 2)
					{
						_any[i].frameX = 0;
					}
				}

				if (i == 0)
				{
					if (_any[i].frameX > 3)
					{
						_any[i].frameX = 0;
					}
				}
			}

			if (_any[0].x < 480)
			{
				_isAnyLeft = false;
			}
		}
	}
}

void pacmanMapScene::anyRender()
{
	for (int i = 0; i < 6; i++)
	{
		_any[i].img->frameRender(getMemDC(), _any[i].x, _any[i].y, _any[i].frameX, _any[i].frameY);
	}
}

void pacmanMapScene::MaptoolSet()
{
	_rc[0] = RectMake(640, 520, 70, 50);	// 아래 버튼 
	_rc[1] = RectMake(760, 520, 70, 50);	// 아래 버튼 
	_rc[2] = RectMake(880, 520, 70, 50);	// 아래 버튼 
	_rc[3] = RectMake(1120, 520, 70, 50);	// 아래 버튼 
	_rc[4] = RectMake(1000, 520, 70, 50);	// 아래 버튼 

	_camera = RectMake(0, 0, 550, 600);					//카메라 관련 샘플은 필요없음	
	_cameraX = 0;										//카메라 관련 샘플은 필요없음	
	_cameraY = 0;										//카메라 관련 샘플은 필요없음	
	_sampleCamera = RectMake(640, 0, WINSIZEX, 390);	//카메라 관련 샘플은 필요없음	
	_sampleCameraX = 640;								//카메라 관련 샘플은 필요없음	
	_sampleCameraY = 0;									//카메라 관련 샘플은 필요없음	

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//게임맵 타일 초기화
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
			//샘플 타일 초기화
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
	//위쪽 버튼 초기화
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
	//샘플맵에 있는 타일 게임맵에 그리기
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
	//위쪽 버튼 눌렀을 때 상황임 map 이란 놈 클릭해야 클릭이 된다. 
	//버튼 0 누르면 접었다 폈다 가능
	//나머지는 스테이지임 
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
		_camera = RectMake(0, 0, 1150, 600);
		for (int i = 0; i < 5; i++)
		{
			_rc[i] = RectMake(WINSIZEX+50, 420, 70, 50);
		}
	}
	if (_button[0].isClick == false)
	{
		_button[0].x = 580;
		_button[0].y = 0;
		_button[1].x = 580;
		_button[1].y = 40;
		_button[2].x = 580;
		_button[2].y = 110;
		_button[3].x = 580;
		_button[3].y = 180;
		_button[4].x = 580;
		_button[4].y = 250;

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
				//이거 클릭한거 보여주기 위해 그려넣음
				IMAGEMANAGER->frameAlphaRender("pacmanMap", getMemDC(), _ptMouse.x, _ptMouse.y, currentTile.x, currentTile.y, 10);
			}
		}
	}

	//타일 토글키로 볼수있다
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
	//위에 버튼 렌더 내코딩 아닌줄 ... 
	if (_button[0].isClick == false)
	{
		IMAGEMANAGER->findImage("maptooMenu")->render(getMemDC(), _button[0].rc.left + 5, _button[0].rc.top);
	}
	if (_button[0].isClick == true)
	{
		IMAGEMANAGER->findImage("maptooMenu1")->render(getMemDC(), _button[0].rc.left + 5, _button[0].rc.top);
	}
	IMAGEMANAGER->findImage("ChangeSampleImgMenu")->render(getMemDC(), _button[1].rc.left + 5, _button[1].rc.top);
	IMAGEMANAGER->findImage("ChangeSampleImgMenu2")->render(getMemDC(), _button[2].rc.left + 5, _button[2].rc.top);
	IMAGEMANAGER->findImage("ChangeSampleImgMenu3")->render(getMemDC(), _button[3].rc.left + 5, _button[3].rc.top);
	IMAGEMANAGER->findImage("ChangeSampleImgMenu4")->render(getMemDC(), _button[4].rc.left + 5, _button[4].rc.top);
}

void pacmanMapScene::cameraMove()
{
	//카메라 움직임 
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
}

void pacmanMapScene::save()
{
	//세이브 한다
	HANDLE file;
	DWORD write;

	file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, tile, sizeof(tagTiles) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);
}

void pacmanMapScene::load()
{
	//로드한다
	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, tile, sizeof(tagTiles) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
}

TERRAIN pacmanMapScene::terrainSelect(int frameX, int frameY)
{
	//음 지형물 설정...
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
