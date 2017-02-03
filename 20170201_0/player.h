#pragma once
#include "gameNode.h"
#include "bullet.h"			//미사일클래스를 사용하기 위해
#include "progressBar.h"	//체력바 클래스 사용하기 위해

//적매니져 상호참조하기 위해 클래스 전방선언
class enemyManager;

class player : public gameNode
{
private:
	image* _rocket;			//로켓(플레이어) 이미지
	missile* _missile;		//미사일 클래스
	missileM1* _missileM1;	//미사일M1 클래스

	enemyManager* _em;		//동적할당 하면 안된다!!!

	progressBar* _hpBar;	//체력바
	float _maxHp, _currentHp;//최대체력, 현재체력	

	//int _x, _y;			//위치 좌표
	//RECT _rc;				//플레이어 렉트
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//플레이어 무브
	//void move();

	//미사일M1 삭제
	void removeMissileM1(int index);

	//충돌함수(플레이어의 총알클래스의 총알벡터과 적매니져의 미니언벡터)
	void collision();

	//체력바 피통깍기
	void hitDamage(float damage);

	//미사일M1 가져오기
	missileM1* getMissileM1() { return _missileM1; }
	image* getPlayerImage() { return _rocket; }

	//상호참조시 적매니져포인터를 넘길 셋터함수
	void setEMLink(enemyManager* em) { _em = em; }

	player() {}
	~player() {}
};

