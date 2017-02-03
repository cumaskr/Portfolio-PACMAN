#pragma once
#include "gameNode.h"

//부모클래스 => 이놈을 상속받아서 보스, 일반몬스터등을 만든다
class enemy : public gameNode
{
private:
	RECT _rc;			//충돌용 렉트
	image* _image;		//에너미 이미지

	//프레임 이미지를 돌리기 위한 변수들
	int _count;
	int _currentFrameX;
	int _currentFrameY;

	//랜덤으로 총알 발사 쿨타임주기
	int _fireCount;
	int _rndFireCount;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(char* imageName, POINT position);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move();			//업데이트에 넣기
	virtual void draw();			//렌더 안에 넣기
	virtual void animation();		//업데이트에 넣기

	bool bulletCountFire(void);

	RECT getRect() { return _rc; }

	enemy() {}
	virtual ~enemy() {}
};

