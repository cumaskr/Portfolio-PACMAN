#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"


HRESULT enemyManager::init(void)
{
	//미니언 생성
	this->setMinion();

	_count = 0;

	//총알클래스 생성 및 초기화
	_bullet = new bullet;
	_bullet->init("bullet", 15, 600);

	return S_OK;
}

void enemyManager::release(void)
{
	//총알클래스 해제
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void enemyManager::update(void)
{
	//벡터에 담긴 미니언들 업데이트
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}

	//총알클래스 업데이트
	_bullet->update();

	//미니언 총알발사
	this->minionBulletFire();

	//충돌처리
	this->collision();

}

void enemyManager::render(void)
{
	//벡터에 담긴 미니언들 렌더
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	_bullet->render();
}

void enemyManager::setMinion(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			enemy* ufo = new minion;
			ufo->init("ufo", PointMake(50 + j * 100, 100 + i * 100));

			_vMinion.push_back(ufo);
		}
	}
}

void enemyManager::minionBulletFire(void)
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 30, -PI / 2, 3.0f);
		}
	}
}

void enemyManager::removeMinion(int index)
{
	_vMinion.erase(_vMinion.begin() + index);
}

//적총알과 플레이어
void enemyManager::collision()
{
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getVBullet()[i].rc,
			&_player->getPlayerImage()->boundingBox()))
		{
			_bullet->removeBullet(i);
			_player->hitDamage(10);
			break;
		}

	}
}
