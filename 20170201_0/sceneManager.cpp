#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

HRESULT sceneManager::init(void)
{
	return S_OK;
}

void sceneManager::release(void)
{
	//정석적인 방법
	miSceneList iter = _mSceneList.begin();
	for (; iter != _mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mSceneList.clear();

	/*
	for each(auto scene in _mSceneList)
	{
		scene.second->release();
		SAFE_DELETE(scene.second);
	}
	*/
}

void sceneManager::update(void)
{
	//현재씬이 존재하면 해당하는 현재씬을 업데이트
	if (_currentScene) _currentScene->update();
}

void sceneManager::render(void)
{
	//현재씬이 존재하면 해당하는 현재씬을 업데이트
	if (_currentScene) _currentScene->render();
}

gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	//씬이 없으니 널값 리턴
	if (!scene) return NULL;

	//씬이 있으니 맵에 담자
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//못찾았다면
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려는 씬과 현재씬이 같냐?
	if (find->second == _currentScene) return E_FAIL;

	//여기까지 왔으면 문제 없으니 씬 초기화 하고 변경해준다
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}
