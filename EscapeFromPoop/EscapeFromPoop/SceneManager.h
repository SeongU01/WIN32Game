#pragma once
#include "Scene.h"


enum class eSceneType
{
	MAINMANU,
	PLAY,
	END = 2,
};

class SceneManager
{
private:
	static SceneManager* instance;
	Scene* Scenes[(UINT)eSceneType::END];
	Scene* currScene=nullptr;
	
public:
	SceneManager();
	~SceneManager();

	void Update();
	void Render();
	static SceneManager* GetInstance();
	static void DestroyInstance();

	
	void InitScene();
	void ChanageScene(eSceneType sceneName);
};

