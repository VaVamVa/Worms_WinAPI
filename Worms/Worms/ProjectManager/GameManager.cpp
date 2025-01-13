#include "framework.h"

/*
#include "Scenes/Worm/SelectScene.h"
*/
#include "Scenes/Worms/EndScene.h"
#include "Scenes/Worms/PlayScene.h"

bool GameManager::devMode = false;

GameManager::GameManager()
{
	CreateBackDeviceContextBuffer();
	
	GameTimer::Get();
	V_KEY;
	CAM;
	EffectManager::Get();

	//SceneManager::Get()->Add("Select", new SelectScene());
	SceneManager::Get()->Add("End", new EndScene());
	SceneManager::Get()->Add("Play", new PlayScene());

	SceneManager::Get()->ChangeScene("Play", "Mario,2");

}

GameManager::~GameManager()
{
	SceneManager::Delete();
	GameTimer::Delete();
	VirtualKeyboard::Delete();
	Camera::Delete();

	DeleteDC(backDC);
	DeleteObject(hBitmap);
}

void GameManager::Update()
{
	if (V_KEY->Down(VK_F2))
		devMode = !devMode;
	GameTimer::Get()->Update();
	V_KEY->Update();
	SceneManager::Get()->Update();
}

void GameManager::Render(HDC hdc)
{
	PatBlt(backDC, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, WHITENESS);

	SceneManager::Get()->Render(backDC);

	GameTimer::Get()->Render(backDC);

	BitBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT,
		backDC, 0, 0, SRCCOPY);
}

void GameManager::CreateBackDeviceContextBuffer()
{
	HDC hdc = GetDC(hWnd);

	backDC = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, CLIENT_WIDTH, CLIENT_HEIGHT);
	SelectObject(backDC, hBitmap);

	SetBkMode(backDC, TRANSPARENT);
}
