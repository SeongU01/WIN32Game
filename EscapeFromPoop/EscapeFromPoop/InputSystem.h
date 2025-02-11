#pragma once
#include"WinApp.h"

class InputSystem
{
public:
	struct MouseState
	{
		MouseState()
		:x(0),y(0),wheel(0),left(false), right(false),middle(false)
		{}
		int x;
		int y;
		int wheel;
		bool left;
		bool right;
		bool middle;
	};

private:
	InputSystem(){}
	~InputSystem() {};

	static InputSystem* instance;

	bool isKeyDown[256]{ 0, };
	bool isKeyUp[256]{ 0, };
	bool isKey[256]{ 0, };

	MouseState curMouse;
	MouseState prevMouse;

public: 
	void InitInput();
	void ResetInput();
	void KeyDown(unsigned int key);
	void KeyUp(unsigned int key);
	bool IsKeyDown(unsigned int key);
	bool IsKeyUp(unsigned int key);
	bool IsKey(unsigned int key);


	void InitMouse();
	void UpdateMouse();

	bool IsSame(const MouseState& a, const MouseState& b);

	const MouseState& GetMouseState();
	const MouseState& GetPrevMouseState();

	static InputSystem* GetInstance();
	static void DestroyInstance();

};

