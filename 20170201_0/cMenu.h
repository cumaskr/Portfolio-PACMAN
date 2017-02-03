#pragma once
#include "gameNode.h"

struct tag_button
{
	float x;
	float y;
	RECT rc;
};

class cMenu :public gameNode
{
private:
	TCHAR buffer[256];
	tag_button mapChoiceRC;
	tag_button mapToolRC;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	cMenu() {}
	~cMenu() {}
};

