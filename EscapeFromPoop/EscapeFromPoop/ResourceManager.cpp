#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = nullptr;

void ResourceManager::InitResouce()
{
	Poop::bitmap = (HBITMAP)LoadImageA(NULL, "bitmap\\poop.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	/////////////////////////////////////////////////////////////////////////////////////////

	const char* PlayerImage[10]
	{
		"bitmap\\playerWait1.bmp",

		"bitmap\\playerWait2.bmp",

		"bitmap\\playerWait3.bmp",

		"bitmap\\playerRunL1.bmp",

		"bitmap\\playerRunL2.bmp",

		"bitmap\\playerRunL3.bmp",

		"bitmap\\playerRunR1.bmp",

		"bitmap\\playerRunR2.bmp",

		"bitmap\\playerRunR3.bmp",

		"bitmap\\playerdie.bmp"
	};

	for (int i = 0; i < 10; i++)
	{
		Player::bitmap[i] = (HBITMAP)LoadImageA(NULL, PlayerImage[i], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}

	////////////////////////////////////////////////////////////////////////
	
	backgroundBitMap1 = (HBITMAP)LoadImageA(NULL, "bitmap\\BG.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	backgroundBitMap2 = (HBITMAP)LoadImageA(NULL, "bitmap\\BG2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	//////////////////////////////////////////////////////////////////////////
	MainMenu::startBG = (HBITMAP)LoadImageA(NULL, "bitmap\\startBG.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	MainMenu::startButton = (HBITMAP)LoadImageA(NULL, "bitmap\\startButton.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
}

ResourceManager* ResourceManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ResourceManager;
	}
	return instance;
}

void ResourceManager::DestroyInstance()
{
	delete instance;
}

