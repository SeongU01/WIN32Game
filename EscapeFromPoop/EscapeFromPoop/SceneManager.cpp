#include "SceneManager.h"
#include "MainMenu.h"
#include "PlayScene.h"

SceneManager* SceneManager::instance = nullptr;


SceneManager::SceneManager()
{
	for (UINT i = 0; i <(UINT)eSceneType::END ; i++)
	{
		Scenes[i] = nullptr;
	}
}

SceneManager::~SceneManager()
{
	for (UINT i = 0; i < (UINT)eSceneType::END; i++)
	{
		delete Scenes[i];
	}
}

void SceneManager::Update()
{
	currScene->Update();
}

void SceneManager::Render()
{
	currScene->Render();
}

SceneManager* SceneManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new SceneManager;
	}
	return instance;
}

void SceneManager::DestroyInstance()
{
	delete instance;
}



void SceneManager::InitScene()
{
	Scenes[0] = new MainMenu;
	Scenes[1] = new PlayScene;


	currScene = Scenes[(UINT)eSceneType::MAINMANU];
}

void SceneManager::ChanageScene(eSceneType sceneName)
{
	currScene = Scenes[(UINT)sceneName];
}






