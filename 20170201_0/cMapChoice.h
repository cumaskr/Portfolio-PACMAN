#pragma once
#include "gameNode.h"
#define MAPMAX 4


struct tag_buttons
{
	RECT rc;
	float x;
	float y;
};

struct tag_mapbutton
{
	RECT rc;
	float x;
	float y;
	image* img;
	int alpha;
};



class cMapChoice : public gameNode
{
private:
	TCHAR buffer[256];

	tag_buttons menu_RC;
	tag_buttons left_button;
	tag_buttons right_button;

	tag_mapbutton map_button[MAPMAX];

public:
	
	void MoveLeftMap();
	void MoveRightMap();
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	cMapChoice() {}
	~cMapChoice() {}
};

