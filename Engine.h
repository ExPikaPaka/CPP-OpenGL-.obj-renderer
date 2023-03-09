#pragma once

class Engine
{
public:
	void Init(HWND hWnd);
	void Play(HWND hWnd);
	void WndResize(int x, int y);
	void PlayerMove(HWND hWnd);
};

