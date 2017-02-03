#pragma once
#include "gameNode.h"

//총알 구조체
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	int count;
};

//=============================================================
//	## bullet ## (공용총알 - 너희들이 만들어라~~~)
//=============================================================
class bullet : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	char* _imageName;	//총알 이미지 키값
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수

public:
	//총알이미지키값, 총알갯수, 총알사거리로 초기화
	HRESULT init(char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//총알발사
	void fire(float x, float y, float angle, float speed);
	//총알무브
	void move(void);

	//총알삭제
	void removeBullet(int index);

	//총알벡터 가져오기
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

public:
	bullet() {}
	~bullet() {}
};

//=============================================================
//	## missile ## (missile[0] => 배열처럼 미리 장전해두고 총알발사)
//=============================================================
class missile : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수

public:
	//총알갯수, 총알사거리로 초기화
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//총알발사
	void fire(float x, float y);
	//총알무브
	void move(void);

	missile() {}
	~missile() {}
};

//=============================================================
//	## missileM1 ## (한발씩 총알 발사하면서 생성하고 자동삭제)
//=============================================================
class missileM1 : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수

public:
	//총알갯수, 총알사거리로 초기화
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//총알발사
	void fire(float x, float y);
	//총알무브
	void move(void);

	//총알삭제
	void removeBullet(int index);

	//총알벡터 가져오기
	vector<tagBullet> getVBullet() { return _vBullet; }

	missileM1() {}
	~missileM1() {}
};
