#pragma once
#include "gameNode.h"

class cIntro : public gameNode
{
private:
	int _alpha;
	bool IsRogo;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	cIntro() {}
	~cIntro() {}
};

