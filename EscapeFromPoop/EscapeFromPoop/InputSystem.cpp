#include "InputSystem.h"

InputSystem* InputSystem::instance = nullptr;

void InputSystem::InitInput()
{
	for (int i = 0; i < 256; i++)
	{
		isKeyDown[i] = false;
		isKeyUp[i] = false;
		isKey[i] = false;
	}
	
	InitMouse();
}

void InputSystem::ResetInput()
{
	for (int i = 0; i < 256; i++)
	{
		isKeyDown[i] = false;
		isKeyUp[i] = false;
	}
}

void InputSystem::KeyDown(unsigned int key)
{
	isKeyDown[key] = true;
	isKey[key] = true;
}

void InputSystem::KeyUp(unsigned int key)
{
	isKeyUp[key] = true;
	isKey[key] = false;
}

bool InputSystem::IsKeyDown(unsigned int key)
{
	return isKeyDown[key];
}

bool InputSystem::IsKeyUp(unsigned int key)
{
	return isKeyUp[key];
}

bool InputSystem::IsKey(unsigned int key)
{
	return isKey[key];
}

void InputSystem::InitMouse()
{
	curMouse.x = global::GetWinApp().GetWidth() / 2;
	curMouse.y = global::GetWinApp().GetHeight() / 2;
	curMouse.wheel = 0;

	curMouse.left = false;
	curMouse.right = false;
	curMouse.middle = false;

	prevMouse = curMouse;

	SetCursorPos(curMouse.x, curMouse.y);
}

void InputSystem::UpdateMouse()
{
	prevMouse = curMouse;

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(global::GetWinApp().GetWindow(), &pt);

	curMouse.x = pt.x;
	curMouse.y = pt.y;
	curMouse.wheel = 0;

	curMouse.left = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
	curMouse.right = (GetKeyState(VK_RBUTTON) & 0x8000) != 0;
	curMouse.middle = (GetKeyState(VK_MBUTTON) & 0x8000) != 0;
}

bool InputSystem::IsSame(const MouseState& a, const MouseState& b)
{
	return (a.x == b.x
		&& a.x == b.y
		&& a.wheel == b.wheel
		&& a.left == b.left
		&& a.right == b.right
		&& a.middle == b.middle);
}

const InputSystem::MouseState& InputSystem::GetMouseState()
{
	return curMouse;
}

const InputSystem::MouseState& InputSystem::GetPrevMouseState()
{
	return prevMouse;
}

InputSystem* InputSystem::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new InputSystem;
	}
	return instance;
}

void InputSystem::DestroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
