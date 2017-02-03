#include "stdafx.h"
#include "cMenu.h"

HRESULT cMenu::init(void)
{

	mapChoiceRC.x = WINSIZEX / 2 - 100;
	mapChoiceRC.y = WINSIZEY - 100;
	mapChoiceRC.rc = RectMakeCenter(mapChoiceRC.x, mapChoiceRC.y, 50, 50);
	mapToolRC.x = WINSIZEX / 2 + 100;
	mapToolRC.y = WINSIZEY - 100;
	mapToolRC.rc = RectMakeCenter(mapToolRC.x, mapToolRC.y, 50, 50);

	return S_OK;
}

void cMenu::release(void)
{

}

void cMenu::update(void)
{
	if (PtInRect(&mapChoiceRC.rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->changeScene("∏ º±≈√");
		}
	}

	if (PtInRect(&mapToolRC.rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{			
			SCENEMANAGER->changeScene("∏ ≈¯");								
		}
	}									
}

void cMenu::render(void)
{
	RectangleMake(getMemDC(), mapChoiceRC.rc);
	TextOut(getMemDC(), mapChoiceRC.x, mapChoiceRC.y, TEXT("∏ º±≈√"), lstrlen(TEXT("∏ º±≈√")));
	RectangleMake(getMemDC(), mapToolRC.rc);
	TextOut(getMemDC(), mapToolRC.x, mapToolRC.y, TEXT("∏ ≈¯"), lstrlen(TEXT("∏ ≈¯")));
}
