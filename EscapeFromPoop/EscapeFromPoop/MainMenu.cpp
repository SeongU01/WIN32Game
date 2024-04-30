#include "MainMenu.h"
#include "RenderSystem.h"

HBITMAP MainMenu::startBG = nullptr;
HBITMAP MainMenu::startButton = nullptr;
MainMenu* MainMenu::instance = nullptr;

void MainMenu::Update()
{
	if (CheckPressButton(&startButton))
	{
		SceneManager::GetInstance()->ChanageScene(eSceneType::PLAY);
	}
}

void MainMenu::Render()
{
	RenderSystem::GetInstance()->DrawBitmap(0, 0, startBG, RGB(255,255,255));
	RenderSystem::GetInstance()->DrawBitmap(startButtonPos.x, startButtonPos.y, startButton, RGB(255, 255, 253));
}


bool MainMenu::CheckPressButton(HBITMAP* button)
{
	const InputSystem::MouseState& mouseState = InputSystem::GetInstance()->GetMouseState();
	const InputSystem::MouseState& prevMouseState = InputSystem::GetInstance()->GetPrevMouseState();

	BITMAP buttonInfo;
	GetObject(*button, sizeof(BITMAP), &buttonInfo);
	float buttonXMin = startButtonPos.x;
	float buttonXMax = startButtonPos.x + buttonInfo.bmWidth;
	float buttonYMin = startButtonPos.y;
	float buttonYMax = startButtonPos.y + buttonInfo.bmHeight;

	if (mouseState.left && !prevMouseState.left)
	{
		return(mouseState.x >= buttonXMin && mouseState.x <= buttonXMax &&
				mouseState.y >= buttonYMin && mouseState.y <= buttonYMax);
	}

	return false;
	
}

MainMenu* MainMenu::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new MainMenu;
	}

	return instance;
}

void MainMenu::DestroyInstance()
{
	delete instance;
}


