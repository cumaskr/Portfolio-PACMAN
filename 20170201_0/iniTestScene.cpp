#include "stdafx.h"
#include "iniTestScene.h"

HRESULT iniTestScene::init(void)
{
	return S_OK;
}

void iniTestScene::release(void)
{
}

void iniTestScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//섹션, 키, 밸류
		INIDATA->addData("우형", "노력", "99");
		INIDATA->addData("호조", "코딩력", "101");
		INIDATA->addData("호조", "감성력", "98");
		INIDATA->addData("용재", "엉뚱함", "88");
		INIDATA->addData("경훈", "사교성", "110");
		INIDATA->addData("승희", "똥머리", "7");
		INIDATA->addData("진수", "주력", "150");
		INIDATA->addData("소현", "졸음", "38");
		INIDATA->addData("언식", "공대감성", "120");
		INIDATA->addData("호조", "코딩력", "150");
		//파일이름으로 세이브
		INIDATA->saveINI("개발3팀");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		int test = INIDATA->loadDataInteger("개발3팀", "호조", "코딩력");
		cout << "호조의 코딩력: " << test << endl;
	}
}

void iniTestScene::render(void)
{
}
