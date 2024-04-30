#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

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
	Music::soundManager->InitMusic();
	Music::soundManager->SetVolume(0.5f);
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


void GameManager::Finalize()
{
	TimeSystem::GetInstance()->DestroyInstance();
	InputSystem::GetInstance()->DestroyInstance();
	RenderSystem::GetInstance()->DestroyInstance();
	ObjectManager::GetInstance()->DestroyInstance();
	ResourceManager::GetInstance()->DestroyInstance();
	ColliderManager::GetInstance()->DestroyInstance();
	SceneManager::GetInstance()->DestroyInstance();
	Music::soundManager->DestroyInstance();
}

void GameManager::Run()
{
	MSG msg;
	while (true)
	{
		
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


GameManager* GameManager::GetInstance()
{
	return nullptr;
}

void GameManager::DestroyInstatnce()
{
}
