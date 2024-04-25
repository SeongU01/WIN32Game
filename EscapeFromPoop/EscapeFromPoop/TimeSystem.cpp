#include "TimeSystem.h"

TimeSystem* TimeSystem::instance = nullptr;
//LARGE_INTEGER TimeSystem::currentTime = { 0, };
//LARGE_INTEGER TimeSystem::previousTime = { 0, };
//LARGE_INTEGER TimeSystem::frequency = { 0, };
//double TimeSystem::deltaTime = 0;
static LARGE_INTEGER previousTime = { 0, };
static LARGE_INTEGER currentTime{ 0, };
static LARGE_INTEGER frequency{ 0, };

static float deltaTime=0;


TimeSystem::TimeSystem()
{
}

TimeSystem::~TimeSystem()
{
}

void TimeSystem::InitTime()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&currentTime);
}

void TimeSystem::UpdateTime()
{
	previousTime = currentTime;

	QueryPerformanceCounter(&currentTime);

	deltaTime =
		(float)(currentTime.QuadPart - previousTime.QuadPart)
		/
		(float)(frequency.QuadPart / 1000);
}

const float TimeSystem::GetDeltaTime()
{
	return deltaTime;
}


TimeSystem* TimeSystem::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new TimeSystem;
	}
	return instance;
}

void TimeSystem::DestroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

