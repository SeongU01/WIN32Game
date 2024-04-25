#include "RenderSystem.h"


HWND hWnd;

HDC playScreenDC;
HDC DrawScreenDC;

HBITMAP backBitmap=nullptr;

RenderSystem* RenderSystem::instance = nullptr;

void RenderSystem::InitRender()
{
	hWnd = global::GetWinApp().GetWindow();

	playScreenDC = GetDC(hWnd);

	DrawScreenDC = CreateCompatibleDC(playScreenDC);
	
	backBitmap = CreateCompatibleBitmap(playScreenDC,
		global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight());
}

void RenderSystem::ReleaseRender()
{
	DeleteObject(backBitmap);

	DeleteDC(DrawScreenDC);

	ReleaseDC(hWnd, playScreenDC);
}

void RenderSystem::BeginDraw()
{
	ClearScreen();
	::SelectObject(DrawScreenDC, backBitmap);
}

void RenderSystem::ClearScreen()
{
	::PatBlt(DrawScreenDC, 0, 0,
		global::GetWinApp().GetWidth(),
		global::GetWinApp().GetHeight(),
		WHITENESS);
}

void RenderSystem::EndDraw()
{
	::BitBlt(playScreenDC, 0, 0,
		global::GetWinApp().GetWidth(),
		global::GetWinApp().GetHeight(),
		DrawScreenDC, 0, 0, SRCCOPY);
}

void RenderSystem::DrawBitmap(int x,int y,HBITMAP hbit,UINT transParentColor)
{
	BITMAP bit;

	HDC tempDC = CreateCompatibleDC(DrawScreenDC);
	HBITMAP oldBitmap=(HBITMAP)SelectObject(tempDC,hbit);
	
	GetObject(hbit, sizeof(BITMAP), &bit);

	::TransparentBlt(DrawScreenDC, x, y, bit.bmWidth, bit.bmHeight, tempDC, 0, 0, bit.bmWidth, bit.bmHeight, transParentColor);

	SelectObject(tempDC,oldBitmap);
	DeleteObject(tempDC);
}

void RenderSystem::DrawText(int x, int y, 
	const char* text, COLORREF color, 
	const wchar_t* fontName, int fontSize)
{
	HFONT hFont=CreateFontW(fontSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, fontName);

	HFONT hOldFont = (HFONT)SelectObject(DrawScreenDC, hFont);
	SetTextColor(DrawScreenDC, color);
	SetBkMode(DrawScreenDC, TRANSPARENT);//배경색 투영하기.
	TextOutA(DrawScreenDC, x, y, text, strlen(text));
	SelectObject(DrawScreenDC, hFont);
	DeleteObject(hFont);
}

RenderSystem* RenderSystem::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new RenderSystem;
	}
	return instance;
}

void RenderSystem::DestroyInstance()
{
	delete instance;
}




