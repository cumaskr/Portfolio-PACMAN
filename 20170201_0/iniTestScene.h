#pragma once
#include "gameNode.h"

class iniTestScene : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	iniTestScene() {}
	~iniTestScene() {}
};

