#pragma once
#include"Object.h"
#include"MainMenu.h"
class ResourceManager
{
private:
	ResourceManager() {}
	~ResourceManager() {}

	static ResourceManager* instance;

public:
	void InitResouce();

	static ResourceManager* GetInstance();
	void DestroyInstance();

	HBITMAP backgroundBitMap1;
	HBITMAP backgroundBitMap2;
};

