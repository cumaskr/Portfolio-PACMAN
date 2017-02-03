#pragma once
#include "singletonBase.h"
/*FMOD를 사용하기 위해*/
#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex_vc.lib")
using namespace FMOD;
//==================================================================
//		## soundManager ## (사운드 매니져)
//==================================================================

//채널, 사운드버퍼
#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 20
#define TOTALSOUNDBUFFER (EXTRACHANNELBUFFER + SOUNDBUFFER)

class soundManager : public singletonBase <soundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System* _system;			//시스템 클래스
	Sound** _sound;				//사운드 클래스
	Channel** _channel;			//채널 클래스

	arrSounds _mTotalSounds;	//맵에 담아둘 사운드들

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//사운드 추가(키값, 파일이름, BGM?, 루프냐?)
	void addSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);

	//사운드 재생 (볼륨 0.0 ~ 1.0 Max)
	void play(string keyName, float volume = 1.0f);
	//사운드 종료
	void stop(string keyName);
	//사운드 일시종료
	void pause(string keyName);
	//사운드 다시재생
	void resume(string keyName);

	//플레이 중이냐?
	bool isPlaySound(string keyName);
	//일시정지 중이냐?
	bool isPauseSound(string keyName);

	soundManager() : _system(NULL), _sound(NULL), _channel(NULL) {}
	~soundManager() {}
};

