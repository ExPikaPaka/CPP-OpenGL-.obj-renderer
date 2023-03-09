#include <Windows.h>
#include "Engine.h"
#include "Camera.h"
#include <gl/GL.h>

Camera camera;

void Engine::WndResize(int x, int y) {
	glViewport(0, 0, x, y);

	float k = x / (float)y;
	float sz = 0.1;

	glLoadIdentity();
	glFrustum(-k * sz, k * sz, -sz, sz, sz * 2, 10000);
}

void Engine::Init(HWND hWnd) {
	
	RECT rct;
	GetClientRect(hWnd, &rct);
	WndResize(rct.right, rct.bottom);
}

void Engine::PlayerMove(HWND hWnd) {
	camera.MoveDirection(GetKeyState('W') < 0 ? 1 : (GetKeyState('S') < 0 ? -1 : 0),
					     GetKeyState('A') < 0 ? -1 : (GetKeyState('D') < 0 ? 1 : 0),
					     0.05);  // 0.05 | 0.5
	RECT rct;
	GetClientRect(hWnd, &rct);
	if(GetKeyState(VK_XBUTTON1) >= 0) camera.Move(rct.right / 2, rct.bottom / 2, 0.2);
	camera.Apply();
						
}

void Engine::Play(HWND hWnd) {
	if (GetForegroundWindow() == hWnd) {
		PlayerMove(hWnd);
	}
	
}

