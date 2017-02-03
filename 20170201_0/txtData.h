#pragma once
#include "singletonBase.h"
//=============================================================
//	## txtData ## (텍스트 데이터)
//=============================================================

class txtData : public singletonBase <txtData>
{
public:
	HRESULT init(void);
	void release(void);

	//세이브
	void txtSave(char* fileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	//로드
	vector<string> txtLoad(char* fileName);
	vector<string> charArraySeparation(char charArray[]);

	txtData() {}
	~txtData() {}
};

