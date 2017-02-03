#pragma once
#include "gameNode.h"
class soundTestScene : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	soundTestScene() {}
	~soundTestScene() {}
};

