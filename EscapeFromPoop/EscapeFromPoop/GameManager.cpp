#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

//bool g_bIsGameOver = false;
//bool msgboxShow = true;
//int g_Score = 0;
//int g_HighScore = 0;
//int g_Timer = 0;


GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::Initialize()
{
	TimeSystem::GetInstance()->InitTime();
	InputSystem::GetInstance()->InitInput();
	RenderSystem::GetInstance()->InitRender();
	ResourceManager::GetInstance()->InitResouce();
	SceneManager::GetInstance()->InitScene();
}

void GameManager::Update()
{
	InputSystem::GetInstance()->UpdateMouse();
	SceneManager::GetInstance()->Update();
	InputSystem::GetInstance()->ResetInput();
}

void GameManager::FixedUpdate()
{
	static float elapsedTime;

	elapsedTime += TimeSystem::GetInstance()->GetDeltaTime();

	while (elapsedTime >= 20) //0.02ÃÊ
	{
		elapsedTime -= 20;
	}
}

void GameManager::Render()
{
	RenderSystem::GetInstance()->BeginDraw();
	SceneManager::GetInstance()->Render();
	RenderSystem::GetInstance()->EndDraw();
	
}

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void GameManager::Finalize()
{
	TimeSystem::GetInstance()->DestroyInstance();
	InputSystem::GetInstance()->DestroyInstance();
	RenderSystem::GetInstance()->DestroyInstance();
	ObjectManager::GetInstance()->DestroyInstance();
	ResourceManager::GetInstance()->DestroyInstance();
	ColliderManager::GetInstance()->DestroyInstance();
	SceneManager::GetInstance()->DestroyInstance();
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void GameManager::Run()
{
	while (true)
	{
		MSG msg;
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			else if (msg.message == WM_KEYDOWN)
			{
				InputSystem::GetInstance()->KeyDown(msg.wParam);
			}

			else if (msg.message == WM_KEYUP)
			{
				InputSystem::GetInstance()->KeyUp(msg.wParam);
			}
			else
			{
				DispatchMessage(&msg);
			}
		}
		else
		{

			TimeSystem::GetInstance()->UpdateTime();

			FixedUpdate();

			Update();

			Render();
		} 
		
	}
}

void GameManager::ResetGame()
{
	/*ObjectManager::GetInstance()->ResetObject();
	msgboxShow = true;*/
}



GameManager* GameManager::GetInstance()
{
	return nullptr;
}

void GameManager::DestroyInstatnce()
{
}
