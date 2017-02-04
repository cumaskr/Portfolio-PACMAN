#pragma once
#include "gameNode.h"
class cPlayer : public gameNode
{
private:

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	cPlayer() {}
	~cPlayer() {}
};

