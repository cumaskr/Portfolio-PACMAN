#pragma once
#include "gameNode.h"
#include "pacmanMapNode.h"
struct tagButton
{
	RECT rc;
	int x, y;
	bool isClick;
};
struct tagFramX
{
	int x, y;
	int frameX;
	int frameY;
	image* img;
};
class pacmanMapScene : public gameNode
{
private:
	tagTiles tile[TILEY][TILEX];
	tagSampleTiles sampleTile[SAMPLETILEY][SAMPLETILEX];
	tagCurrentTiles currentTile;
	tagButton _button[5];


	RECT _rc[5];
	RECT _camera;
	RECT _sampleCamera;
	int _cameraX, _cameraY;
	int _sampleCameraX, _sampleCameraY;
	int _sampleCameraX1, _sampleCameraY1;


	float frameX, frameY;
	CTRL mouse;
	image* _sampleImg;
	RECT _line;

	bool _isAnyLeft;
	tagFramX _any[6];
	int _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void check();

	//맵툴 중간에 애니메이션 
	void anyInit();
	void anyTime();
	void anyRender();

	//맵툴 초기화
	void MaptoolSet();
	//샘플이미지 옆 버튼 초기화
	void buttoninit();
	//왼쪽 맵 타일그리기
	void Map();
	//버튼 클릭하기
	void buttonClick();
	//왼쪽맵 렌더
	void MapRender();
	//샘플이미지 옆 버튼 렌더
	void buttonRender();
	//카메라 움직임
	void cameraMove();
	//세이브
	void save();
	//로드
	void load();

	TERRAIN terrainSelect(int frameX, int frameY);

	pacmanMapScene() {}
	~pacmanMapScene() {}
};

