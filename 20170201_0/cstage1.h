#pragma once
#include "gameNode.h"
#include"pacmanMapTool.h"
class cstage1 : public gameNode
{
private:
	pacmanMapTool* _map;
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	cstage1() {}
	~cstage1() {}
};

