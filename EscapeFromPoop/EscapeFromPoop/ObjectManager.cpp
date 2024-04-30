#include "ObjectManager.h"


std::random_device rd;//난수생성
std::mt19937 gen(rd());
std::uniform_int_distribution<int> poopX(0, 455);//똥의 랜덤하게 x좌표 받기
std::uniform_int_distribution<int> poopSpeed(4, 8);//똥이 떨어지는 속도 랜덤받기

float poopCreateInterval = 500;//똥의 생성간격


Player* gPlayer = nullptr;
ObjectManager* ObjectManager::instance = nullptr;
Poop* gPoopArray[MAX_POOP] = { nullptr, };


ObjectManager* ObjectManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ObjectManager;
	}
	return instance;
}

void ObjectManager::DestroyInstance()
{
	ObjectManager::GetInstance()->ResetPoop();
	delete gPlayer;
	delete instance;
}

void ObjectManager::RenderObject()
{
	RenderSystem::GetInstance()->DrawBitmap(0,0, ResourceManager::GetInstance()->backgroundBitMap2,RGB(254,254,254));//배경 그리기
	RenderSystem::GetInstance()->DrawBitmap(0,550, ResourceManager::GetInstance()->backgroundBitMap1, RGB(255, 255, 255));//툴바 그려주기
	for (size_t i = 0; i < MAX_POOP; i++)
	{
		if (gPoopArray[i] != nullptr)
		{
			RenderSystem::GetInstance()->DrawBitmap(gPoopArray[i]->x, gPoopArray[i]->y, gPoopArray[i]->bitmap, RGB(255, 255, 255));
		}
	}
	RenderSystem::GetInstance()->DrawBitmap(gPlayer->x, gPlayer->y, gPlayer->bitmap[gPlayer->status], RGB(255, 255, 255));
}

void ObjectManager::UpdataeObject(bool* g_bIsGameOver,int& score)
{
	ObjectManager::GetInstance()->UpdatePoop(score);
	ObjectManager::GetInstance()->UpdatePlayer(g_bIsGameOver);
	ObjectManager::GetInstance()->MakePoop();
}

void ObjectManager::FixedUpdateObject(bool* g_bIsGameOver)
{
}

void ObjectManager::ResetObject()
{
	ObjectManager::GetInstance()->ResetPlayer();
	ObjectManager::GetInstance()->ResetPoop();
	poopCreateInterval = 500;
}


//-------------------------------------------------------------------------------------------------------------------//

void ObjectManager::MakePoop()
{
	static float elapsedtime;
	static float decreaseInterval;

	
	decreaseInterval += TimeSystem::GetInstance()->GetDeltaTime();
	elapsedtime += TimeSystem::GetInstance()->GetDeltaTime();
	

	if (decreaseInterval > 3000)
	{
		poopCreateInterval = poopCreateInterval * 0.9f;
		decreaseInterval -= 3000;
	}

	if (elapsedtime > poopCreateInterval)
	{
		for (size_t i = 0; i < MAX_POOP; i++)
		{
			if (gPoopArray[i] == nullptr)
			{
				gPoopArray[i] = new Poop;
				gPoopArray[i]->y = 0;
				gPoopArray[i]->x = poopX(gen);
				gPoopArray[i]->speed = poopSpeed(gen);
				break;
			}
		}
		elapsedtime -= poopCreateInterval;
	}

}

Poop* ObjectManager::DeletePoop(Poop* poop)
{
	Poop* temp = poop;
	delete temp;
	poop = nullptr;
	
	return poop;
}



void ObjectManager::UpdatePoop(int&score)
{
	for (size_t i = 0; i < MAX_POOP; i++)
	{
		if (gPoopArray[i] != nullptr)
		{
			gPoopArray[i]->y += gPoopArray[i]->speed * TimeSystem::GetInstance()->GetDeltaTime() * 0.07f;
			if (gPoopArray[i]->y >= 515)
			{
				Poop* temp = gPoopArray[i];
				delete temp;
				gPoopArray[i] = nullptr;

				score++;
			}
		}
	}
}

void ObjectManager::ResetPoop()
{
	for (size_t i = 0; i < MAX_POOP; i++)
	{
		if (gPoopArray[i] != nullptr)
		{
			gPoopArray[i]=ObjectManager::GetInstance()->DeletePoop(gPoopArray[i]);
		}
	}

}



//--------------------------------------------------------------------------------------------------------------------------------------------//

void ObjectManager::MakePlayer()
{
	gPlayer = new Player;
	gPlayer->x = 240;
	gPlayer->y = 504;
	gPlayer->speed = 0.4f;
	gPlayer->status = 0;
}

void ObjectManager::UpdatePlayer(bool* g_bIsGameOver)
{
	static float elapsedTime;
	elapsedTime += TimeSystem::GetInstance()->GetDeltaTime();


	if (InputSystem::GetInstance()->IsKey(VK_LEFT))
	{
		gPlayer->Move(-(gPlayer->speed * TimeSystem::GetInstance()->GetDeltaTime()), 0);
		if (gPlayer->x < 0)
		{
			gPlayer->Move((gPlayer->speed * TimeSystem::GetInstance()->GetDeltaTime()), 0);
		}
	}
	if (InputSystem::GetInstance()->IsKey(VK_RIGHT))
	{
		gPlayer->Move((gPlayer->speed * TimeSystem::GetInstance()->GetDeltaTime()), 0);
		if (gPlayer->x >455)
		{
			gPlayer->Move(-(gPlayer->speed * TimeSystem::GetInstance()->GetDeltaTime()), 0);
		}
	}

	if (elapsedTime >= 150)
	{
		if (InputSystem::GetInstance()->IsKey(VK_LEFT)&&!InputSystem::GetInstance()->IsKey(VK_RIGHT))
		{
			gPlayer->MoveL();
		}
		else if (InputSystem::GetInstance()->IsKey(VK_RIGHT)&&!InputSystem::GetInstance()->IsKey(VK_LEFT))
		{
			gPlayer->MoveR();
		}
		else
		{
			gPlayer->Stop();
		}
		elapsedTime -= 150;
	}
	
	for (int i = 0; i < MAX_POOP; i++)
	{
		if (gPoopArray[i] != nullptr)
		{
			if (ColliderManager::GetInstance()->ColliderAWithB(gPlayer, gPoopArray[i], gPlayer->status, gPoopArray[i]->status))
			{
				Music::soundManager->PlayMusic(Music::eSoundList::death, Music::eSoundChannel::Effect);
				gPlayer->status = 9;
				*g_bIsGameOver = true;
			}
		}
	}
}

void ObjectManager::ResetPlayer()
{
	gPlayer->x = 240;
}





