#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init(void)
{
	return S_OK;
}

HRESULT enemy::init(char * imageName, POINT position)
{
	//프레임 초기화
	_count = 0;
	_currentFrameX = _currentFrameY = 0;

	//이미지, 이미지렉트 초기화
	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());

	//랜덤으로 총알 쿨타임 주기
	_fireCount = 0;
	_rndFireCount = RND->getFromIntTo(1, 1000);

	return S_OK;
}

void enemy::release(void)
{
}

void enemy::update(void)
{
	move();
	animation();
}

void enemy::render(void)
{
	draw();
}

//알아서
void enemy::move()
{
}

void enemy::draw()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void enemy::animation()
{
	_count++;
	if (_count % 3 == 0)
	{
		_image->setFrameX(_image->getFrameX() + 1);
		_currentFrameX++;
		if (_currentFrameX >= _image->getMaxFrameX())
		{
			_currentFrameX = 0;
			_count = 0;
		}
	}
}

bool enemy::bulletCountFire(void)
{
	_fireCount++;
	if (_fireCount % _rndFireCount == 0)
	{
		_rndFireCount = RND->getFromIntTo(1, 1000);
		_fireCount = 0;
		return true;
	}

	return false;
}
