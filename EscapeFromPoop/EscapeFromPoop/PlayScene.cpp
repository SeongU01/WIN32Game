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
		if (!isPlayMusic)//노래틀기
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
			Music::soundManager->StopMusic(Music::eSoundChannel::BGM);//노래끄기
			isPlayMusic = false;
			InputSystem::GetInstance()->InitInput();//키 초기화
			MessageBoxA(global::GetWinApp().GetWindow(), "죽었습니다. space bar를 누르면 재시작합니다.", "알림", MB_OK);
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
	std::string ScoreText = "점수 : " + std::to_string(g_Score);

	std::string highScoreText = "최고 점수 : " + std::to_string(g_HighScore);

	std::string timer = "시간 : " + std::to_string(g_Timer) + "초";

	RenderSystem::GetInstance()->DrawText(15, 565, ScoreText.c_str(), RGB(0, 0, 0), L"궁서체", 20);
	
	RenderSystem::GetInstance()->DrawText(180, 565, highScoreText.c_str(), RGB(0, 0, 0), L"궁서체", 20);

	RenderSystem::GetInstance()->DrawText(370, 565, timer.c_str(), RGB(0, 0, 0), L"궁서체", 20);
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
