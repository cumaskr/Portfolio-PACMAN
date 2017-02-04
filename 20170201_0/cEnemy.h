#pragma once
#include "gameNode.h"
class cEnemy : public gameNode
{
private:


public:


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	cEnemy() {}
	~cEnemy() {}
};

