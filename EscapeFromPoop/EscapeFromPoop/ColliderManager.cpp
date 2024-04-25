#include "ColliderManager.h"

ColliderManager* ColliderManager::instance = nullptr;


ColliderManager* ColliderManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ColliderManager;
	}
	return instance;
}

void ColliderManager::DestroyInstance()
{
	delete instance;
}


