#include "stdafx.h"
#include "cMapChoice.h"

void cMapChoice::MoveLeftMap()
{
	for (int i = 0; i < MAPMAX; i++)
	{
		map_button[i].x -= 100;		
	}
}

void cMapChoice::MoveRightMap()
{
	for (int i = 0; i < MAPMAX; i++)
	{
		map_button[i].x += 100;
	}
}

HRESULT cMapChoice::init(void)
{
	left_button.x = WINSIZEX / 2-100;
	left_button.y = WINSIZEY-100;
	right_button.x = WINSIZEX / 2+100;
	right_button.y = WINSIZEY-100;
	left_button.rc = RectMakeCenter(left_button.x, left_button.y, 50, 50);
	right_button.rc = RectMakeCenter(right_button.x, right_button.y, 50, 50);


	for (int i = 0; i < MAPMAX; i++)
	{
		map_button[i].x = WINSIZEX / 2 -100 + 100*i ;
		map_button[i].y = WINSIZEY / 2;
		map_button[i].rc = RectMakeCenter(map_button[i].x, map_button[i].y, 50, 50);	
		map_button[i].img = IMAGEMANAGER->findImage("¾ËÆÄ50");
		map_button[i].alpha = 0;
	}


	return S_OK;
}

void cMapChoice::release(void)
{

}

void cMapChoice::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&left_button.rc,_ptMouse))
		{
			MoveLeftMap();
		}
		if (PtInRect(&right_button.rc, _ptMouse))
		{
			MoveRightMap();
		}
	}


	for (int i = 0; i < MAPMAX; i++)
	{
		if (map_button[i].x == WINSIZEX/2)
		{
			map_button[i].alpha = 0;
		}
		else
		{
			map_button[i].alpha = 200;
		}
		map_button[i].rc = RectMakeCenter(map_button[i].x, map_button[i].y, 50, 50);
	}
	
}

void cMapChoice::render(void)
{
	RectangleMake(getMemDC(), left_button.rc);
	RectangleMake(getMemDC(), right_button.rc);

	for (int i = 0; i < MAPMAX; i++)
	{
		RectangleMake(getMemDC(), map_button[i].rc);
		map_button[i].img->alphaRender(getMemDC(),map_button[i].rc.left, map_button[i].rc.top,map_button[i].alpha);
	}
}
