#pragma once
#include "gameNode.h"

class sceneTest : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sceneTest() {}
	~sceneTest() {}
};

