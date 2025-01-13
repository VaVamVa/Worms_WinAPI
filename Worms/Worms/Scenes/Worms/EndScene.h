#pragma once

class EndScene : public Scene
{
private:
	const float SHOW_TIME = 5.0f;

public:
	EndScene();
	~EndScene();

	void Update() override;
	void Render(HDC hdc) override;

	void Start(std::string msg) override;
	void End() override;

private:
	float time = 0.0f;
	std::string winMsg = " team Win!";
};