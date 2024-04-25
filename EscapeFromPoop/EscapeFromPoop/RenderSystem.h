#pragma once
#pragma comment(lib,"Msimg32.lib")

#include"Resource.h"
#include"WinApp.h"
#include<string>

class RenderSystem
{
private:
	RenderSystem() {}
	~RenderSystem() {};

	static RenderSystem* instance;

public:
	
	void InitRender();
	void ReleaseRender();

	void BeginDraw();
	void ClearScreen();
	void EndDraw();

	void DrawBitmap(int x, int y, HBITMAP hbit, UINT transParentColor);
	void DrawText(int x, int y,
		const char* text, COLORREF color,
		const wchar_t* fontName, int fontSize);


	static RenderSystem* GetInstance();
	static void DestroyInstance();
};
