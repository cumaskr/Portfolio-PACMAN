#pragma once
#include "singletonBase.h"
#include <time.h>
//====================================================================
//			## randomFunction ## (랜덤펑션)
//====================================================================

class randomFunction : public singletonBase <randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction() {}

	HRESULT init() { return S_OK; }

	//getInt
	inline int getInt(int num) { return rand() % num; }
	//getFromIntTo => 주의사항 0이 나오면 뻥난다
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
	//getFloat
	inline float getFloat(float num)
	{
		return ((float)rand() / (float)RAND_MAX) * num;
	}
	//getFromFloatTo
	inline float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}
};

