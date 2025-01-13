#include "framework.h"
#include "PlayScene.h"

PlayScene::PlayScene()
{
	AUDIO->Add("Mario", "Resources/Sounds/Mario_BGM.mp3", true, true);
}

PlayScene::~PlayScene()
{
	SAFE_DELETE(background);
	SAFE_DELETE(land);
}

void PlayScene::Update()
{
	AUDIO->Update();
	WormsManager::Get()->Update();
	BulletManager::Get()->Update();
	EffectManager::Get()->Update();
	CAM->Update();
}

void PlayScene::Render(HDC hdc)
{
	background->CamRender(hdc, 0.2f);
	land->CamRender(hdc);
	WormsManager::Get()->Render(hdc);
	BulletManager::Get()->Render(hdc);
	EffectManager::Get()->CamRender(hdc);
}

void PlayScene::Start(std::string msg)
{
	std::vector<std::string> msgValues = string_parser::SplitString(msg, ",");
	curFile = msgValues[0];
	std::string landFileNameA = "Resources/Textures/Land_" + curFile + ".bmp";
	std::wstring landFileNameW = std::wstring().assign(landFileNameA.begin(), landFileNameA.end());

	if (curFile == "Mario")
	{
		AUDIO->Play(curFile);
		background = new ImageRect(L"Resources/Textures/Background_Mario.bmp");
		Texture::Renewal(landFileNameW);
		land = new ImageRect(landFileNameW);
		WormsManager::Get()->SetLandTexture(land->GetTexture());
		WormsManager::Get()->Spawn(curFile, std::stoi(msgValues[1]));
	}

	background->SetPos(background->GetSize() * 0.5f);
	land->SetPos(land->GetSize() * 0.5f);
	CAM->SetMap(background);


	BulletManager::Get();
}

void PlayScene::End()
{
	AUDIO->Stop(curFile);
	SAFE_DELETE(background);
	SAFE_DELETE(land);
}
