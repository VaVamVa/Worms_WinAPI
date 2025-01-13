#include "framework.h"

GameTimer::GameTimer()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);

	timeScale = deltaScale / static_cast<float>(periodFrequency);
}

void GameTimer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	elapsedTime = static_cast<float>(currentTime - lastTime) * timeScale;

	frameCount++;
	untilOneSecondCounting += elapsedTime;
	if (untilOneSecondCounting >= 1.0f)
	{
		frameRate = frameCount;
		frameCount = 0;
		untilOneSecondCounting = 0.0f;
	}

	lastTime = currentTime;
}

void GameTimer::Render(HDC hdc)
{
	std::wstring str = L"FPS : " + std::to_wstring(frameRate);
	W_TEXT(hdc, 5, 5, str);
	/*
	str = L"Delta : " + std::to_wstring(elapsedTime);
	W_TEXT(hdc, 5, 20, str);
	*/
}
