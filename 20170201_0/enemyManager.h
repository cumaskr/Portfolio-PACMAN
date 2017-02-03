#pragma once
#include "gameNode.h"
#include "minion.h"
#include "bullet.h"

//상호참조용 플레이어 클래스 전방선언
class player;

class enemyManager : public gameNode
{
private:
	vector<enemy*> _vMinion;
	vector<enemy*>::iterator _viMinion;

	bullet* _bullet;
	int _count;

	player* _player;	//동적할당 하면 안된다!!!

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//미니언 세팅 => 초기화에 넣어줄것
	void setMinion(void);

	//미니언 총알발사
	void minionBulletFire(void);

	//미니언 삭제
	void removeMinion(int index);

	//충돌함수
	void collision();

	//미니언 벡터 가져오기
	vector<enemy*> getVMinion() { return _vMinion; }

	//상호참조시 플레이어포인터를 넘길 셋터함수
	void setPlayerLink(player* player) { _player = player; }

	enemyManager() {}
	~enemyManager() {}
};

