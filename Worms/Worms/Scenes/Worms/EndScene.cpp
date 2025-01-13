#include "framework.h"
#include "EndScene.h"

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
}

void EndScene::Update()
{
	if (time < SHOW_TIME)
	{
		time += DELTA;
		return;
	}
	
	// Map Select
	SceneManager::Get()->ChangeScene("Play", "Mario,3");
}

void EndScene::Render(HDC hdc)
{
	A_TEXT(hdc, CLIENT_WIDTH >> 1, CLIENT_HEIGHT >> 1, winMsg);
}

void EndScene::Start(std::string msg)
{
	winMsg = msg;
	if (msg != "Draw")
		winMsg += " team Win!";
}

void EndScene::End()
{
	winMsg = "";
	time = 0.0f;
}
