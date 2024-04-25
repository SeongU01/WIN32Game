#pragma once
#include "WinApp.h"
#include "TimeSystem.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "ColliderManager.h"

class GameManager
{
private:
	static GameManager* instance;

public:
	GameManager();
	~GameManager();

	void Initialize();

	void Update();

	void FixedUpdate();

	void Render();

	void Finalize();

	void Run();

	void ResetGame();

	static GameManager* GetInstance();

	static void DestroyInstatnce();


};

