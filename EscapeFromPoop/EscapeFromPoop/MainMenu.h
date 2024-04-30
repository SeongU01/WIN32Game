#pragma once
#include"Scene.h"
#include"SceneManager.h"
struct pair
{
	float x;
	float y;
};

class MainMenu :public Scene
{
private:
	static MainMenu* instance;
	const pair startButtonPos{ 310,400 };

public:
	MainMenu()
	{
		SceneManager::GetInstance()->ChanageScene(eSceneType::MAINMANU);
	}
	~MainMenu() 
	{
		DestroyInstance();
	};
	static HBITMAP startBG;
	static HBITMAP startButton;

	void Update()override;
	void Render()override;

	bool CheckPressButton(HBITMAP* button);

	static MainMenu* GetInstance();
	void DestroyInstance();
};

