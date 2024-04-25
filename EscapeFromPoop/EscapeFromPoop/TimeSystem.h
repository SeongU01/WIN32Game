#pragma once
#include<Windows.h>
class TimeSystem
{
private:
	TimeSystem();
	~TimeSystem();

	//static LARGE_INTEGER previousTime;
	//static LARGE_INTEGER currentTime;
	//static LARGE_INTEGER frequency;
	//
	//static double deltaTime;

	static TimeSystem* instance;

public:
	
	void InitTime();
	void UpdateTime();
	const float GetDeltaTime();

	static TimeSystem* GetInstance();
	static void DestroyInstance();

};
