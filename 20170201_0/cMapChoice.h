#pragma once
#include "gameNode.h"
#define MAPMAX 5
#define MAPBUTTONSIZEX 250
#define MAPBUTTONSIZEY 150
enum BUTTON_STATE
{
	BUTTON_IDLE,
	BUTTON_LRESET,
	BUTTON_RRESET,
	BUTTON_LEFT,
	BUTTON_RIGHT,
};

struct tag_buttons
{
	RECT rc;
	float x;
	float y;
	float angle;
	float gravity;
};

struct tag_mapbutton
{
	RECT rc;
	float x;
	float y;
	int alpha;
	int state;
	float angle;
	float gravity;
};



class cMapChoice : public gameNode
{
private:
	TCHAR buffer[123];
	int frontIndex = 0;
	int endIndex = 0;
	int centerIndex = 0;
	int centerIndexPlus = EOF;
	int centerIndexMinus = EOF;
	bool IsMapMove;

	tag_buttons menu_RC;      // 좌상단 메뉴상자
	tag_buttons back_RC;      // 좌상단 메뉴상자
	tag_buttons map_nameRC;      // 가운데 맵이름
	tag_buttons left_button;  //왼쪽버튼
	tag_buttons right_button; //오른쪽버튼

	tag_mapbutton map_button[MAPMAX]; // 맵5개

public:

	void MapMoveCheck();
	void MoveButton();
	void MoveLeftMap();
	void MoveRightMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	cMapChoice() {}
	~cMapChoice() {}
};

