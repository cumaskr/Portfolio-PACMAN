#pragma once
#include "gameNode.h"
class cLight : public gameNode
{
private:

public:


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	cLight() {}
	~cLight() {}
};

