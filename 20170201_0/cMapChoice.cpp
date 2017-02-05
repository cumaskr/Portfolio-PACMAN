#include "stdafx.h"
#include "cMapChoice.h"

HRESULT cMapChoice::init(void)
{
	IsMapMove = false;
	frontIndex = 0;
	centerIndex = 2;
	endIndex = MAPMAX - 1;

	menu_RC.x = 200;
	menu_RC.y = 100;
	menu_RC.angle = PI / 2;
	menu_RC.gravity = 0.0f;
	menu_RC.rc = RectMakeCenter(menu_RC.x, menu_RC.y, 200, 100);

	back_RC.x = WINSIZEX - 200;
	back_RC.y = 100;
	back_RC.rc = RectMakeCenter(back_RC.x, back_RC.y, 200, 100);

	for (int i = 0; i < MAPMAX; i++)
	{
		map_button[i].x = (MAPBUTTONSIZEX + 50)*i;
		map_button[i].y = WINSIZEY / 2 + 50;
		map_button[i].rc = RectMakeCenter(map_button[i].x, map_button[i].y, MAPBUTTONSIZEX, MAPBUTTONSIZEY);
		map_button[i].alpha = 100;
		map_button[i].state = BUTTON_IDLE;
		map_button[i].gravity = 0.0f;
	}

	left_button.x = WINSIZEX / 2 - 200;
	left_button.y = WINSIZEY - 50;

	right_button.x = WINSIZEX / 2 + 200;
	right_button.y = WINSIZEY - 50;

	left_button.rc = RectMakeCenter(left_button.x, left_button.y, 50, 50);
	right_button.rc = RectMakeCenter(right_button.x, right_button.y, 50, 50);

	map_nameRC.x = WINSIZEX / 2;
	map_nameRC.y = WINSIZEY - 50;
	map_nameRC.rc = RectMakeCenter(map_nameRC.x, map_nameRC.y, 300, 70);

	map_button[2].alpha = 255;

	return S_OK;
}

void cMapChoice::release(void)
{

}

void cMapChoice::update(void)
{
	// 메뉴 위아래로 통통로직
	menu_RC.gravity += 0.1f;
	menu_RC.y += -sinf(menu_RC.angle) * 2 + menu_RC.gravity;
	if (menu_RC.gravity >= 3.8)
	{
		menu_RC.gravity = 0.0f;
	}
	menu_RC.rc = RectMakeCenter(menu_RC.x, menu_RC.y, 200, 100);

	MoveButton();
	MapMoveCheck();

	// 맵이 움직이고난후에 좌우버튼과 스테이지변경 버튼 활성화
	if (IsMapMove == false)
	{
		// 왼쪽버튼 오른쪽버튼
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&left_button.rc, _ptMouse))
			{
				IsMapMove = true;
				MoveLeftMap();
			}
			if (PtInRect(&right_button.rc, _ptMouse))
			{
				IsMapMove = true;
				MoveRightMap();
			}
			if (PtInRect(&back_RC.rc, _ptMouse))
			{
				SCENEMANAGER->changeScene("메인메뉴");
			}
			//////////////// 스테이지 전환!//////////////////
			if (PtInRect(&map_button[2].rc, _ptMouse))
			{
				SCENEMANAGER->changeScene("1스테이지");
			}
		}
	}

	// 맵버튼 움직임 연동시키기!
	for (int i = 0; i < MAPMAX; i++)
	{
		map_button[i].rc = RectMakeCenter(map_button[i].x, map_button[i].y, MAPBUTTONSIZEX, MAPBUTTONSIZEY);
	}

}

void cMapChoice::render(void)
{
	IMAGEMANAGER->findImage("선택_백그라운드2")->render(getMemDC());
	IMAGEMANAGER->findImage("선택_메뉴")->render(getMemDC(), menu_RC.rc.left, menu_RC.rc.top);
	//RectangleMake(getMemDC(), left_button.rc);
	//RectangleMake(getMemDC(), right_button.rc);
	//RectangleMake(getMemDC(), menu_RC.rc);
	//RectangleMake(getMemDC(), map_nameRC.rc);
	//RectangleMake(getMemDC(), back_RC.rc);

	//맵이름글자랜더
	if (centerIndexPlus == EOF&&centerIndexMinus == EOF)
	{
		IMAGEMANAGER->findImage("메뉴_이름3")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
	}

	if (centerIndexPlus != EOF)
	{
		if (centerIndexPlus == 0)
		{
			IMAGEMANAGER->findImage("메뉴_이름1")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexPlus == 1)
		{
			IMAGEMANAGER->findImage("메뉴_이름2")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexPlus == 2)
		{
			IMAGEMANAGER->findImage("메뉴_이름3")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexPlus == 3)
		{
			IMAGEMANAGER->findImage("메뉴_이름4")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexPlus == 4)
		{
			IMAGEMANAGER->findImage("메뉴_이름5")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
	}
	else
	{
		if (centerIndexPlus == 0)
		{
			IMAGEMANAGER->findImage("메뉴_이름1")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexPlus == 1)
		{
			IMAGEMANAGER->findImage("메뉴_이름2")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexPlus == 2)
		{
			IMAGEMANAGER->findImage("메뉴_이름3")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexPlus == 3)
		{
			IMAGEMANAGER->findImage("메뉴_이름4")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexPlus == 4)
		{
			IMAGEMANAGER->findImage("메뉴_이름5")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
	}
	if (centerIndexMinus != EOF)
	{
		if (centerIndexMinus == 0)
		{
			IMAGEMANAGER->findImage("메뉴_이름1")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexMinus == 1)
		{
			IMAGEMANAGER->findImage("메뉴_이름2")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexMinus == 2)
		{
			IMAGEMANAGER->findImage("메뉴_이름3")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexMinus == 3)
		{
			IMAGEMANAGER->findImage("메뉴_이름4")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexMinus == 4)
		{
			IMAGEMANAGER->findImage("메뉴_이름5")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
	}
	else
	{
		if (centerIndexMinus == 0)
		{
			IMAGEMANAGER->findImage("메뉴_이름1")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexMinus == 1)
		{
			IMAGEMANAGER->findImage("메뉴_이름2")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexMinus == 2)
		{
			IMAGEMANAGER->findImage("메뉴_이름3")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexMinus == 3)
		{
			IMAGEMANAGER->findImage("메뉴_이름4")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
		if (centerIndexMinus == 4)
		{
			IMAGEMANAGER->findImage("메뉴_이름5")->render(getMemDC(), map_nameRC.rc.left, map_nameRC.rc.top);
		}
	}

	//맵이미지랜더
	IMAGEMANAGER->findImage("선택_맵5")->alphaRender(getMemDC(), map_button[4].rc.left, map_button[4].rc.top, map_button[4].alpha);
	IMAGEMANAGER->findImage("선택_맵4")->alphaRender(getMemDC(), map_button[3].rc.left, map_button[3].rc.top, map_button[3].alpha);
	IMAGEMANAGER->findImage("선택_맵1")->alphaRender(getMemDC(), map_button[2].rc.left, map_button[2].rc.top, map_button[2].alpha);
	IMAGEMANAGER->findImage("선택_맵2")->alphaRender(getMemDC(), map_button[1].rc.left, map_button[1].rc.top, map_button[1].alpha);
	IMAGEMANAGER->findImage("선택_맵3")->alphaRender(getMemDC(), map_button[0].rc.left, map_button[0].rc.top, map_button[0].alpha);

	//왼쪽버튼 오른쪽버튼 확대축소
	if (PtInRect(&left_button.rc, _ptMouse))
	{
		IMAGEMANAGER->findImage("선택_버튼2")->frameRender(getMemDC(), left_button.rc.left, left_button.rc.top, 0, 0);
	}
	else
	{
		IMAGEMANAGER->findImage("선택_버튼")->frameRender(getMemDC(), left_button.rc.left, left_button.rc.top, 0, 0);
	}
	if (PtInRect(&right_button.rc, _ptMouse))
	{
		IMAGEMANAGER->findImage("선택_버튼2")->frameRender(getMemDC(), right_button.rc.left, right_button.rc.top, 1, 0);
	}
	else
	{
		IMAGEMANAGER->findImage("선택_버튼")->frameRender(getMemDC(), right_button.rc.left, right_button.rc.top, 1, 0);
	}
	if (PtInRect(&back_RC.rc, _ptMouse))
	{
		IMAGEMANAGER->findImage("선택_메뉴3")->render(getMemDC(), back_RC.rc.left, back_RC.rc.top);
	}
	else
	{
		IMAGEMANAGER->findImage("선택_메뉴2")->render(getMemDC(), back_RC.rc.left, back_RC.rc.top);
	}

}

void cMapChoice::MapMoveCheck()
{
	if (IsMapMove == true)
	{
		for (int i = 0; i < MAPMAX; i++)
		{
			if (map_button[i].state == BUTTON_IDLE)
			{
				continue;
			}
			else
			{
				return;
			}
		}
		IsMapMove = false;
	}
}

void cMapChoice::MoveButton()
{
	for (int i = 0; i < MAPMAX; i++)
	{
		if (map_button[i].state == BUTTON_LEFT)
		{
			centerIndexMinus = EOF;
			map_button[i].x -= 5;
			if (centerIndex + 1 >= MAPMAX)
			{
				centerIndexPlus = centerIndex + 1 - MAPMAX;
			}
			else if (centerIndex + 1 < MAPMAX)
			{
				centerIndexPlus = centerIndex + 1;
			}
			map_button[centerIndex].alpha = 100;
			map_button[centerIndexPlus].alpha = 255;
			if (map_button[centerIndexPlus].x <= WINSIZEX / 2)
			{
				map_button[i].state = BUTTON_IDLE;
			}
		}
		if (map_button[i].state == BUTTON_RIGHT)
		{
			centerIndexPlus = EOF;
			map_button[i].x += 5;
			if (centerIndex - 1 < 0)
			{
				centerIndexMinus = centerIndex - 1 + MAPMAX;
			}
			else if (centerIndex - 1 >= 0)
			{
				centerIndexMinus = centerIndex - 1;
			}
			map_button[centerIndex].alpha = 100;
			map_button[centerIndexMinus].alpha = 255;
			if (map_button[centerIndexMinus].x >= WINSIZEX / 2)
			{
				map_button[i].state = BUTTON_IDLE;
			}
		}

		if (map_button[i].state == BUTTON_LRESET)
		{
			if (map_button[i].y>WINSIZEY / 2 + 50)
			{
				map_button[i].y = WINSIZEY / 2 + 50;
				map_button[i].x = WINSIZEX;
				map_button[i].gravity = 0.0f;
				map_button[i].state = BUTTON_IDLE;
				endIndex = i;
				if (i + 3 > 4)
				{
					centerIndex = i + 3 - 5;
				}
				else
				{
					centerIndex = i + 3;
				}
				return;
			}
			map_button[i].angle = PI / 4;
			map_button[i].gravity += 0.08f;
			map_button[i].x += cosf(map_button[i].angle) * 13;
			map_button[i].y += -sinf(map_button[i].angle) * 8 + map_button[i].gravity;
		}
		if (map_button[i].state == BUTTON_RRESET)
		{
			if (map_button[i].y>WINSIZEY / 2 + 50)
			{
				map_button[i].y = WINSIZEY / 2 + 50;
				map_button[i].x = 0;
				map_button[i].gravity = 0.0f;
				map_button[i].state = BUTTON_IDLE;
				frontIndex = i;
				if (i - 3 < 0)
				{
					centerIndex = i - 3 + 5;
				}
				else
				{
					centerIndex = i - 3;
				}
				return;
			}
			map_button[i].angle = 3 * PI / 4;
			map_button[i].gravity += 0.08f;
			map_button[i].x += cosf(map_button[i].angle) * 13;
			map_button[i].y += -sinf(map_button[i].angle) * 8 + map_button[i].gravity;
		}
	}
}

void cMapChoice::MoveLeftMap()
{

	for (int i = 0; i < MAPMAX; i++)
	{
		if (i == frontIndex)
		{
			map_button[i].state = BUTTON_LRESET;
		}
		else
		{
			map_button[i].state = BUTTON_LEFT;
		}
	}
	frontIndex++;
	if (frontIndex == MAPMAX)
	{
		frontIndex = 0;
	}
}

void cMapChoice::MoveRightMap()
{

	for (int i = 0; i < MAPMAX; i++)
	{
		if (i == endIndex)
		{
			map_button[i].state = BUTTON_RRESET;
		}
		else
		{
			map_button[i].state = BUTTON_RIGHT;
		}
	}
	endIndex--;
	if (endIndex < 0)
	{
		endIndex += MAPMAX;
	}
}