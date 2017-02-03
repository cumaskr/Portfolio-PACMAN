#pragma once
#include "image.h"

//����� �̹����� ���������� ����� �α�
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;				//HDC
	bool _managerInit;		//�Ŵ��� �ʱ�ȭ �߳�?

public:
	
	virtual HRESULT init(bool managerInit);
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//����� �̹��� ���
	image* getBackBuffer(void) { return _backBuffer; }
	//�޸� DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC ��� (ȭ��DC)
	HDC getHDC() { return _hdc; }

	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode() {}
	virtual ~gameNode() {}
};