#pragma once
#include"Scene.h"
#include"ObjectManager.h"
#include<string>
class PlayScene :public Scene
{
public:
	PlayScene()
	{
		ObjectManager::GetInstance()->MakePlayer();
	}
	~PlayScene(){}

	int score = 0;
	int highScore = 0;
	int timer = 0;

	void Update()override;
	void Render()override;

	void RenderUI();
	
	void UpdateTimer();
	void ResetGame();
};
