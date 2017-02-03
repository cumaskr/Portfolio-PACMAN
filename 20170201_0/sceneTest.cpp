#include "stdafx.h"
#include "sceneTest.h"


HRESULT sceneTest::init(void)
{
	return S_OK;
}

void sceneTest::release(void)
{
}

void sceneTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->changeScene("픽셀충돌");
	}
}

void sceneTest::render(void)
{
	char str[128];
	sprintf(str, "씬테스트 중임~~~~");
	TextOut(getMemDC(), 100, 100, str, strlen(str));
}
