#pragma once

class ImageRect : public Rect
{
private:

public:
	ImageRect(std::wstring fileName,
		int frameX = 1, int frameY = 1,
		COLORREF transparentColor = RGB(255, 0, 255)
	);
	ImageRect(Texture* texture);
	~ImageRect();

	void Render(HDC hdc, POINT curFrame = {}, bool isTransparent = true);
	void CamRender(HDC hdc, POINT curFrame = {}, bool isTransparent = true);
	void CamRender(HDC hdc, float speed, POINT curFrame = {}, bool isTransparent = true);

	void SetImageToObjectSize(GameObject* object);

	Texture* GetTexture() { return this->texture; }

protected:
	Texture* texture;
	POINT maxFrame;

	Rect camRect;
};