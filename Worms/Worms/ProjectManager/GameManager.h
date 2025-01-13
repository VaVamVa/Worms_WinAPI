#pragma once

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update();
	void Render(HDC hdc);

	static const bool DevMode() { return devMode; }

private:
	void CreateBackDeviceContextBuffer();

private:
	HDC backDC;
	HBITMAP hBitmap;

	static bool devMode;
};