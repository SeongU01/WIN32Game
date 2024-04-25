#pragma once
#include "WinApp.h"
#include <random>
#include "RenderSystem.h"
#include "ResourceManager.h"
#include "ColliderManager.h"
#include "SceneManager.h"
#include "Object.h"

class ObjectManager
{
private:
	static ObjectManager* instance;

public:
	ObjectManager() {}
	~ObjectManager() {}

	static ObjectManager* GetInstance();
	static void DestroyInstance();
	void RenderObject();
	void UpdataeObject(bool* g_bIsGameOver,int& score);
	void FixedUpdateObject(bool* g_bIsGameOver);
	void ResetObject();

	//poop
	void MakePoop();
	Poop* DeletePoop(Poop* poop);
	void UpdatePoop(int& score);
	void ResetPoop();

	
	//Player
	void MakePlayer();
	void UpdatePlayer(bool* g_bIsGameOver);
	void ResetPlayer();


};
