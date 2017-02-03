#include "stdafx.h"
#include "soundTestScene.h"

HRESULT soundTestScene::init(void)
{
	//사운드 추가
	SOUNDMANAGER->addSound("사운드1", "브금.mp3");
	SOUNDMANAGER->addSound("사운드2", "브금1.mp3");

	SOUNDMANAGER->play("사운드1");

	return S_OK;
}

void soundTestScene::release(void)
{
}

void soundTestScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (SOUNDMANAGER->isPlaySound("사운드1"))
		{
			SOUNDMANAGER->stop("사운드1");
			SOUNDMANAGER->play("사운드2");
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		SOUNDMANAGER->pause("사운드2");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->resume("사운드2");
	}
}

void soundTestScene::render(void)
{
}
