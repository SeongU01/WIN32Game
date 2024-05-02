#include "PlayScene.h"
#include "CSound.h"

bool g_bIsGameOver = false;
bool msgboxShow = true;
int g_Score = 0;
int g_HighScore = 0;
int g_Timer = 0;

void PlayScene::Update()
{
	if (!g_bIsGameOver)
	{
		if (!isPlayMusic)//�뷡Ʋ��
		{
			Music::soundManager->PlayMusic(Music::eSoundList::MainBGM, Music::eSoundChannel::BGM);
			isPlayMusic = true;
		}
		ObjectManager::GetInstance()->UpdataeObject(&g_bIsGameOver,g_Score);
		UpdateTimer();
	}
	else
	{
		if (msgboxShow)
		{
			Music::soundManager->StopMusic(Music::eSoundChannel::BGM);//�뷡����
			isPlayMusic = false;
			InputSystem::GetInstance()->InitInput();//Ű �ʱ�ȭ
			MessageBoxA(global::GetWinApp().GetWindow(), "�׾����ϴ�. space bar�� ������ ������մϴ�.", "�˸�", MB_OK);
			msgboxShow = false;
		}

		if (InputSystem::GetInstance()->IsKeyDown(VK_SPACE))
		{
			g_bIsGameOver = false;
			
			ResetGame();
		}

	}
}

void PlayScene::Render()
{
	ObjectManager::GetInstance()->RenderObject();
	RenderUI();
}

void PlayScene::RenderUI()
{
	std::string ScoreText = "���� : " + std::to_string(g_Score);

	std::string highScoreText = "�ְ� ���� : " + std::to_string(g_HighScore);

	std::string timer = "�ð� : " + std::to_string(g_Timer) + "��";

	RenderSystem::GetInstance()->DrawText(15, 565, ScoreText.c_str(), RGB(0, 0, 0), L"�ü�ü", 20);
	
	RenderSystem::GetInstance()->DrawText(180, 565, highScoreText.c_str(), RGB(0, 0, 0), L"�ü�ü", 20);

	RenderSystem::GetInstance()->DrawText(370, 565, timer.c_str(), RGB(0, 0, 0), L"�ü�ü", 20);
}

void PlayScene::UpdateTimer()
{
	static float elapsedTime;
	elapsedTime += TimeSystem::GetInstance()->GetDeltaTime();

	if (elapsedTime >= 1000)
	{
		g_Timer++;
		elapsedTime -= 1000;
	}
}

void PlayScene::ResetGame()
{
	ObjectManager::GetInstance()->ResetObject();
	msgboxShow = true;
	if (g_HighScore < g_Score)
	{
		g_HighScore = g_Score;
	}
	g_Score = 0;
	g_Timer = 0;
}
