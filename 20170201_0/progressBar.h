#pragma once
#include "gameNode.h"
//=============================================================
//	## progressBar ## (프로그래스바 = 체력바)
//=============================================================

class progressBar : public gameNode
{
private:
	TCHAR buffer[256];
	RECT _rcProgress;			//체력바 렉트
	int _x, _y;					//체력바 위치 좌표
	float _width;				//체력바 가로길이
	float _height;				//체력바 세로길이(나중에 필요하면 수정하기)

	image* _progressBarFront;	//체력바 앞 이미지
	image* _progressBarBack;		//체력바 뒤 이미지


public:
	//체력바 초기화(앞이미지키,백이미지키, x, y, 가로길이, 세로길이)
	HRESULT init(char* frontImageKey, char* backImageKey, int x, int y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	//체력바 게이지 세팅하기
	void setGauge(float currentHp, float maxHp);

	image* GetImage() { return _progressBarFront; }

	float GetWidth() { return _width; }
	//체력바 위치 좌표 세팅하기
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	//체력바 렉트 가져오기
	RECT getRect(void) { return _rcProgress; }

	progressBar() {}
	~progressBar() {}
};

