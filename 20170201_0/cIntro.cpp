#include "stdafx.h"
#include "cIntro.h"

HRESULT cIntro::init(void)
{
	_alpha = 0;
	IMAGEMANAGER->addImage("인트로백그라운드", "intro_back.bmp",800,800,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("인트로하얀색", "intro_white.bmp", 800, 800, true, RGB(255, 0, 255));

	return S_OK;
}

void cIntro::release(void)
{

}

void cIntro::update(void)
{
	int static nCount = 0;
	nCount++;
	if (nCount%1==0)
	{
		_alpha+=10;
	}
	if (_alpha>=255)
	{
		SCENEMANAGER->changeScene("로딩화면");
	}
}

void cIntro::render(void)
{
	IMAGEMANAGER->findImage("인트로백그라운드")->render(getMemDC());
	IMAGEMANAGER->findImage("인트로하얀색")->alphaRender(getMemDC(), _alpha);
}
