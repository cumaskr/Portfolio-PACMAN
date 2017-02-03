#pragma once
#include "singletonBase.h"

class playerData : public singletonBase <playerData>
{
private:
	int _hp;

public:
	HRESULT init(void);
	void release(void);

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }

	playerData() {}
	~playerData() {}
};

