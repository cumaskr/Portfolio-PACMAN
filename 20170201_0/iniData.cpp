#include "stdafx.h"
#include "iniData.h"

HRESULT iniData::init(void)
{
	return S_OK;
}

void iniData::release(void)
{
}
//데이터 추가하기(섹션, 키, 밸류)
void iniData::addData(char * section, char * key, char * value)
{
	//ini데이터 구조체 선언후 초기화
	tagIniData data;
	data.section = section;
	data.key = key;
	data.value = value;

	//벡터에 ini데이터 구조체 담기
	_vIniData.push_back(data);
}

//세이브(파일이름)
void iniData::saveINI(char * fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		WritePrivateProfileString(_vIniData[i].section, _vIniData[i].key, _vIniData[i].value, dir);
	}
}
//문자로 값을 로드하기(파일이름, 섹션, 키)
char * iniData::loadDataString(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	char data[64] = { NULL };
	GetPrivateProfileString(section, key, "", data, 64, dir);

	return data;
}

//정수로 값을 로드하기(파일이름, 섹션, 키)
int iniData::loadDataInteger(char * fileName, char * section, char * key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(str, "\\%s.ini", fileName);
	GetCurrentDirectory(256, dir);
	strcat(dir, str);

	return GetPrivateProfileInt(section, key, 0, dir);
}
