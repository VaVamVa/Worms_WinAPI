#pragma once

class Texture
{
private:
	Texture(std::wstring file,
		int frameX, int frameY,
		COLORREF transparentColor
	);
	~Texture();

public:
	static Texture* Add(std::wstring file,
		int frameX = 1, int frameY = 1,
		COLORREF transparentColor = RGB(255, 0, 255)
	);
	static void Renewal(std::wstring file);
	static void Delete();

	void Render(HDC hdc, class GameObject* object, POINT curFrame, bool isTransparent = true);
	void Render(HDC hdc, Rect* cam, POINT curFrame, bool isTransparent = true);

	SIZE GetImageSize() const { return imageSize; }
	SIZE GetFrameSize() const { return cutSize; }
	POINT GetFrame() const { return imageFrame; }
	void SetImageToObjectSize(class GameObject* object);
	
	const float GetEffectivePixelUnderPosY(const Vector2D& pos);
	const bool IsEffectivePixelPosY(const Vector2D& pos);

	HDC GetMemDC() const { return memDC; }
	const COLORREF GetTransparentColor() const { return transparentColor; }

	bool IsSprite() { return imageFrame.x == 1 && imageFrame.y == 1; }

private:
	HDC memDC;
	HBITMAP hBitmap;

	COLORREF transparentColor;

	SIZE imageSize, cutSize;
	POINT imageFrame = {};

	static std::unordered_map<std::wstring, Texture*> textures;
};