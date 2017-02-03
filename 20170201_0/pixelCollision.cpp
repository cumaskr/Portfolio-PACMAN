#include "stdafx.h"
#include "pixelCollision.h"


HRESULT pixelCollision::init(void)
{
	//백그라운드 이미지
	_mountain = IMAGEMANAGER->addImage("mountain", "mountain.bmp", 800, 600, true, RGB(255, 0, 255));

	//공 이미지
	_ball = IMAGEMANAGER->addImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	//공 위치 초기화
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	//y축으로 탐지(공의 하단에 사각형 만들기)
	_probeY = _y + _ball->getHeight() / 2;

	_rc1 = RectMakeCenter(_ptMouse.x, _ptMouse.y, 100, 100);

	return S_OK;
}

void pixelCollision::release(void)
{
}

void pixelCollision::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 3.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 3.0f;
	}
	//공의 렉트도 움직여주자
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());
	//y축으로 탐지(공의 하단에 사각형 만들기)
	_probeY = _y + _ball->getHeight() / 2;

	/*이부분이 픽셀충돌 핵심*/
	//탐지할 Y값의 범위를 위아래로 원하는 만큼 검사를 한다
	for (int i = _probeY - 20; i < _probeY + 20; i++)
	{
		COLORREF color = GetPixel(_mountain->getMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}
	}


	_rc1 = RectMakeCenter(_ptMouse.x, _ptMouse.y, 100, 100);

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		SCENEMANAGER->changeScene("씬테스트");
	}

}

void pixelCollision::render(void)
{
	//백그라운드 렌더
	//_mountain->render(getMemDC());
	IMAGEMANAGER->render("백그라운드", getMemDC());

	//공 이미지 렌더
	_ball->render(getMemDC(), _rc.left, _rc.top);

	if (KEYMANAGER->isToggleKey('A'))
	{
		//작은 사각형 렌더
		Rectangle(getMemDC(), _x, _probeY, _x + 10, _probeY + 10);
	}

	Rectangle(getMemDC(), _rc1.left, _rc1.top, _rc1.right, _rc1.bottom);

}
