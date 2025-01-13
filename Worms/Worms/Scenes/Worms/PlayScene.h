#pragma once

#include "Objects/Worms/Worm.h"
#include "Objects/Worms/WormsManager.h"
#include "Objects/Bullets/BulletManager.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene을(를) 통해 상속됨
	void Update() override;
	void Render(HDC hdc) override;

	void Start(std::string msg) override;
	void End() override;

private:
	ImageRect* background;
	ImageRect* land;

	std::string curFile = "";
};