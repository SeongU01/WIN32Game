#include "stdafx.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "TimeSystem.h"
#include "Object.h"
#include "DoubleLinkedList.h"

#include <stdio.h>	
#include <ConsoleApi.h>

#define MAX_ENEMY 10


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

BoxAirplane g_player;
//BoxAirplane g_enemy[MAX_ENEMY];
BoxAirplane g_enemy;
DoubleLinkedList<BoxAirplane> g_enemyList;


//체크할 때 너무 느려 3초에서 1초로 조정. 기능은 정상 작동.
float enemyCreateInterval = 1.0f;



// 비주얼 스튜디오가 만든 템플릿은 다른 추가적인 내용이 많아 이해하기 어려워 가장 간단하게 작성함.

// 윈도우 프로시저 함수 선언
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void UpdateGame();
void RenderGame();

// 프로젝트 속성 -> 링커 -> 시스템 -> 하위 시스템 -> Windows로 변경
// 진입점 함수 정의
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 윈도우 클래스 구조체 초기화
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	// 윈도우 프로시저 함수
	wc.hInstance = hInstance;   // 인스턴스 핸들
	// NULL을 사용하면 현재 실행 중인 프로그램의 인스턴스 핸들을 사용하게 됩니다.두 번째 인자는 로드할 커서의 ID입니다.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = L"BasicWindowClass";

	// 윈도우 클래스 등록
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"윈도우 클래스 등록 실패", L"에러", MB_OK | MB_ICONERROR);
		return 1;
	}

	// 원하는 크기가 조정되어 리턴
	SIZE clientSize = { 800, 600 };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	// 윈도우 생성
	HWND hwnd = CreateWindowEx(
		0,
		L"BasicWindowClass",
		L"간단한 윈도우",
		WS_OVERLAPPEDWINDOW,	// OR연산으로 조합된 윈도우창 스타일
		0, 0,	// 시작위치
		clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, // 너비, 높이
		NULL, NULL, hInstance, NULL
	);

	if (!hwnd)
	{
		MessageBox(NULL, L"윈도우 생성 실패", L"에러", MB_OK | MB_ICONERROR);
		return 1;
	}

	// 윈도우 표시
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	bool bUseConsole = false;
	if (bUseConsole)
	{
		AllocConsole();
		FILE* _tempFile;
		freopen_s(&_tempFile, "CONOUT$", "w", stdout);
	}

	Render::InitRender(hwnd, clientSize.cx, clientSize.cy);
	Input::InitInput(hwnd, clientSize.cx, clientSize.cy);
	Time::InitTime();

	g_player.Init(true);
	

	// 대기가 없는 메세지 루프
	MSG msg;
	while (true)
	{
		// 메시지가 있으면 처리, 없으면 바로 게임 루프로 이동
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// WM_QUIT 메시지 확인
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 게임 루프					
			UpdateGame();
			RenderGame();
		}
	}

	Input::ReleaseInput();
	Render::ReleaseRender();
	
	for (DoubleLinkedList<BoxAirplane>::Iterator iter = g_enemyList.Begin(); iter != g_enemyList.End(); )
	{
		iter = g_enemyList.Erase(iter.GetCurrentNode());
	}
	


	if (bUseConsole)
	{
		FreeConsole();
	}
	//메모리 릭 확인용
	_CrtDumpMemoryLeaks();
	return static_cast<int>(msg.wParam);
}

// 윈도우 프로시저 함수 정의
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void UpdateGame()
{
	Time::UpdateTime();
	float deltaTime = Time::GetDeltaTime();
	Input::Update();

	static float elapsedTime;
	elapsedTime += deltaTime;

	g_player.m_inputDirX = 0;
	g_player.m_inputDirY = 0;
	if (Input::IsCurrDn(VK_LEFT))
	{
		g_player.m_inputDirX = -1;
	}
	else if (Input::IsCurrDn(VK_RIGHT))
	{
		g_player.m_inputDirX = 1;
	}
	if (Input::IsCurrDn(VK_UP))
	{
		g_player.m_inputDirY = -1;
	}
	else if (Input::IsCurrDn(VK_DOWN))
	{
		g_player.m_inputDirY = 1;
	}
	if (Input::IsTurnDn('O'))
	{
		std::cout << g_player.m_posX << ' ' << g_player.m_posY << std::endl;
	}
	if (Input::IsCurrDn(VK_LBUTTON))
	{
		POINT pt = Input::GetMouseClient();
		std::cout << pt.x << ' ' << pt.y << std::endl;
	}
	if (Input::IsTurnDn('T'))
	{
		std::cout << deltaTime << std::endl;
	}

	//몬스터 만들기
	if (elapsedTime >= enemyCreateInterval)
	{
		g_enemy.Init(false);
		g_enemyList.PushBack(g_enemy);
		elapsedTime -= enemyCreateInterval;
	}

	// 위치 갱신
	g_player.Update(deltaTime);

	for (DoubleLinkedList<BoxAirplane>::Iterator iter = g_enemyList.Begin(); iter != g_enemyList.End(); ++iter)
	{
		g_enemy = *iter;
		g_enemy.Update(deltaTime);
		*iter = g_enemy;
	}


	
	//충돌확인
	for (DoubleLinkedList<BoxAirplane>::Iterator iter = g_enemyList.Begin(); iter != g_enemyList.End();)
	{
		g_enemy=*iter;
		if (g_enemy.m_isDead == false)
		{
			if (g_player.Collide(g_enemy))
			{
				g_enemy.m_isDead = true;

				iter = g_enemyList.Erase(iter.GetCurrentNode());
				continue;
			}
		}
		++iter;
	}
}
void RenderGame()
{
	Render::BeginDraw();
	g_player.Render();
	for (DoubleLinkedList<BoxAirplane>::Iterator iter=g_enemyList.Begin(); iter != g_enemyList.End();++iter)
	{
		g_enemy = *iter;
		g_enemy.Render();
	}
	Render::EndDraw();
}