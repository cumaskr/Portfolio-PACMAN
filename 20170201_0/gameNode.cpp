#include "stdafx.h"
#include "gameNode.h"

//==================================================================
//		## 초기화 ## init(void)
//==================================================================
HRESULT gameNode::init(void)
{
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;
	
	if (managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);		//타이머 초기화
		KEYMANAGER->init();					//키매니져 초기화
		RND->init();						//랜덤펑션 초기화
		IMAGEMANAGER->init();				//이미지매니져 초기화
		PLAYERDATA->init();					//플레이어데이터 초기화
		TXTDATA->init();					//텍스트데이터 초기화
		SCENEMANAGER->init();				//씬매니져 초기화
		INIDATA->init();					//INI데이터 초기화
		TIMEMANAGER->init();				//타임매니져 초기화
		SOUNDMANAGER->init();				//사운드매니져 초기화
	}

	return S_OK;
}

//==================================================================
//		## 해제 ## release(void)
//==================================================================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//타이머 해제
		//KillTimer(_hWnd, 1);
		//키매니져 싱글톤 해제
		KEYMANAGER->releaseSingleton();
		//랜덤펑션 싱글톤 해제
		RND->releaseSingleton();
		//이미지매니져 해제, 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//플레이어데이터 싱글톤 해제
		PLAYERDATA->releaseSingleton();
		//텍스트데이터 싱글톤 해제
		TXTDATA->releaseSingleton();
		//INI데이터 싱글톤 해제
		INIDATA->releaseSingleton();
		//씬매니져 해제, 싱글톤 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//타임매니져 싱글톤 해제
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		//사운드매니져 해제, 싱글톤 해제
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
	}

	//DC 해제
	ReleaseDC(_hWnd, _hdc);
}

//==================================================================
//		## 업데이트 ## update(void)
//==================================================================
void gameNode::update(void)
{
	//새로고침 (나중에 고성능 타이머를 만든 후에는 사용하지 않는다)
	//더블버퍼링 이후 사용하지 않는다 (true => false)
	//나중에 테스트 하기 (true / false or 걍지우기)
	//InvalidateRect(_hWnd, NULL, FALSE);
}
//==================================================================
//		## 렌더 ## render(void)
//==================================================================
void gameNode::render(void)
{
}

//==================================================================
//		## MainProc ## 메인프로시져
//==================================================================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}