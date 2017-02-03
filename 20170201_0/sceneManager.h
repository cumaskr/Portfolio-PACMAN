#pragma once
#include "singletonBase.h"
//==================================================================
//		## sceneManager ## (씬 매니져)
//==================================================================

//싱글톤을 상속받은 아이들은 static으로 만들어 지기때문에
//일반클래스인 게임노드를 사용하려고 하면 터진다

//게임노드 클래스 전방선언
class gameNode;

class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	mSceneList _mSceneList;		//각각의 씬(화면)들을 담아둘 맵
	gameNode* _currentScene;	//현재씬

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//값 초기화 시켜주는 방법
	//1. 생성자에서 바로 초기화
	//2. 멤버이니셜라이즈를 통해서 초기화
	//3. 셋터함수를 통해서

	//씬추가
	gameNode* addScene(string sceneName, gameNode* scene);

	//씬변경
	HRESULT changeScene(string sceneName);

	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};

