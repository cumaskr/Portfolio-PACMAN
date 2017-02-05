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
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			//로딩이 완료 됐으니 씬변경
			SCENEMANAGER->changeScene("메인메뉴");
		}
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////우형
	_loading->loadImage("알파50", "mapchoice_white.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴_메뉴", "menu_1.bmp", 500, 100, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴_게임", "menu_2.bmp", 200, 100, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴_게임2", "menu_2_big.bmp", 210, 110, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴_맵툴", "menu_3.bmp", 200, 100, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴_맵툴2", "menu_3_big.bmp", 210, 110, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴_종료", "menu_4.bmp", 200, 100, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴_종료2", "menu_4_big.bmp", 210, 110, true, RGB(255, 0, 255));

	_loading->loadImage("선택_백그라운드", "choice_back.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("선택_백그라운드2", "choice_back2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("선택_메뉴", "choice_menu.bmp", 200, 100, true, RGB(255, 0, 255));
	_loading->loadImage("선택_메뉴2", "choice_menu2.bmp", 200, 100, true, RGB(255, 0, 255));
	_loading->loadImage("선택_메뉴3", "choice_menu2_big.bmp", 210, 110, true, RGB(255, 0, 255));
	_loading->loadImage("선택_맵1", "choice_map1.bmp", 250, 150, true, RGB(255, 0, 255));
	_loading->loadImage("선택_맵2", "choice_map2.bmp", 250, 150, true, RGB(255, 0, 255));
	_loading->loadImage("선택_맵3", "choice_map3.bmp", 250, 150, true, RGB(255, 0, 255));
	_loading->loadImage("선택_맵4", "choice_map4.bmp", 250, 150, true, RGB(255, 0, 255));
	_loading->loadImage("선택_맵5", "choice_map5.bmp", 250, 150, true, RGB(255, 0, 255));
	_loading->loadFrameImage("선택_버튼", "choice_button.bmp", 100, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("선택_버튼2", "choice_button_big.bmp", 110, 60, 2, 1, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴_이름1", "choice_name1.bmp", 300, 70, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴_이름2", "choice_name2.bmp", 300, 70, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴_이름3", "choice_name3.bmp", 300, 70, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴_이름4", "choice_name4.bmp", 300, 70, true, RGB(255, 0, 255));
	_loading->loadImage("메뉴_이름5", "choice_name5.bmp", 300, 70, true, RGB(255, 0, 255));


///////////////////////////////////////////////////////////////////////////////////////////////////////////승희
	_loading->loadFrameImage("pacmanMap", "pacmanMap1.bmp", 600, 300, 20, 10);
	//_loading->loadImage("maptooMenu", "maptooMenu0.bmp", 20, 30, true, RGB(255, 0, 255));
	_loading->loadImage("ChangeSampleImgMenu", "ChangeSampleImgMenu.bmp", 20, 50, true, RGB(255, 0, 255));
	_loading->loadImage("ChangeSampleImgMenu2", "ChangeSampleImgMenu2.bmp", 20, 50, true, RGB(255, 0, 255));

	//맵툴씬 관련 이미지들
	_loading->loadImage("maptooMenu", "maptooMenu0.bmp", 20, 30, true, RGB(255, 0, 255));
	_loading->loadImage("maptooMenu1", "maptooMenu1.bmp", 20, 30, true, RGB(255, 0, 255));
	_loading->loadImage("ChangeSampleImgMenu", "ChangeSampleImgMenu.bmp", 20, 50, true, RGB(255, 0, 255));
	_loading->loadImage("ChangeSampleImgMenu2", "ChangeSampleImgMenu2.bmp", 20, 50, true, RGB(255, 0, 255));
	_loading->loadImage("ChangeSampleImgMenu3", "ChangeSampleImgMenu3.bmp", 20, 50, true, RGB(255, 0, 255));
	_loading->loadImage("ChangeSampleImgMenu4", "ChangeSampleImgMenu4.bmp", 20, 50, true, RGB(255, 0, 255));
	_loading->loadImage("save", "save.bmp", 70, 50, true, RGB(255, 0, 255));
	_loading->loadImage("saveBig", "saveBig.bmp", 105, 70, true, RGB(255, 0, 255));
	_loading->loadImage("load", "load.bmp", 70, 50, true, RGB(255, 0, 255));
	_loading->loadImage("loadBig", "loadBig.bmp", 105, 70, true, RGB(255, 0, 255));
	_loading->loadImage("back", "back.bmp", 70, 50, true, RGB(255, 0, 255));
	_loading->loadImage("backBig", "backBig.bmp", 105, 70, true, RGB(255, 0, 255));
	_loading->loadImage("draw", "draw.bmp", 83, 50, true, RGB(255, 0, 255));
	_loading->loadImage("drawBig", "drawBig.bmp", 105, 70, true, RGB(255, 0, 255));
	_loading->loadImage("map", "map.bmp", 70, 50, true, RGB(255, 0, 255));
	_loading->loadImage("mapBig", "mapBig.bmp", 105, 70, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptoolPacmanAny", "maptoolPacmanAny.bmp", 102, 70, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptoolEnemyAny0", "maptoolEnemyAny0.bmp", 76, 70, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptoolEnemyAny1", "maptoolEnemyAny1.bmp", 76, 70, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptoolEnemyAny2", "maptoolEnemyAny2.bmp", 76, 70, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptoolEnemyAny3", "maptoolEnemyAny3.bmp", 76, 70, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("maptoolEnemyAny4", "maptoolEnemyAny4.bmp", 76, 70, 2, 2, true, RGB(255, 0, 255));

}
//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound(void)
{
}
