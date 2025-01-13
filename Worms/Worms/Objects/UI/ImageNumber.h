#pragma once

class ImageNumber : public ImageRect
{
public:
	enum Alignment
	{
		LEFT, RIGHT, CENTER
	};

public:
	ImageNumber(std::wstring fileName, int frameX = 10, int frameY = 1);
	~ImageNumber() = default;

	void Render(HDC hdc);

	void SetValue(int value);
	void SetAlignment(Alignment alignment) { this->alignment = alignment; }

private:
	std::string text;
	Alignment alignment = LEFT;
};