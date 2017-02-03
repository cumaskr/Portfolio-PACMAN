#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//로딩클래스 생성 및 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//로딩클래스 해제
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	if (_loading->loadingDone())
	{
		//로딩이 완료 됐으니 씬변경
		SCENEMANAGER->changeScene("메인메뉴");
	}
}

void loadingScene::render(void)
{
	//로딩클래스 렌더
	_loading->render();
}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage(void)
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들어 놓자
	for (int i = 0; i < 10; i++)
	{
		_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	}
	//백그라운드 이미지
	_loading->loadImage("백그라운드", "background.bmp", WINSIZEX, WINSIZEY);	
	_loading->loadImage("알파50", "mapchoice_white.bmp", 50, 50, true, RGB(255, 0, 255));

}
//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound(void)
{
}
