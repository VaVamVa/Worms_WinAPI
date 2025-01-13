#pragma once

class GameTimer : public Singleton<GameTimer>
{
private:
	const float EPSILON = 0.01f;

private:
	friend Singleton;
	GameTimer();
	~GameTimer() = default;

public:
	void Update();
	void Render(HDC hdc);

	float GetElapsedTime() { return elapsedTime > EPSILON ? EPSILON : elapsedTime * deltaScale; }
	void SetDeltaScale(float value = 1.0f) { this->deltaScale = value; }

private:
	__int64 periodFrequency = 0;
	float timeScale = 0.0f;
	float deltaScale = 1.0f;

	int frameRate = 0;
	int frameCount = 0;
	int lockFps = 0;

	float untilOneSecondCounting = 0.0f;

	__int64 currentTime = 0;
	__int64 lastTime = 0;
	float elapsedTime = 0.0f;
};