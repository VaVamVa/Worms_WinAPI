#include "framework.h"

ImageNumber::ImageNumber(std::wstring fileName, int frameX, int frameY)
	:ImageRect(fileName, frameX, frameY)
{
}

void ImageNumber::Render(HDC hdc)
{
	int num = 0;
	FOR(i, 0, text.length())
	{
		num = text[i] - '0';

        switch (alignment)
        {
        case ImageNumber::LEFT:
            pos.x += i * size.x;
            break;
        case ImageNumber::RIGHT:
            pos.x += i * size.x - text.length() * size.x;
            break;
        case ImageNumber::CENTER:
            pos.x += i * size.x - text.length() * size.x * 0.5f;
            break;
        }

        ImageRect::Render(hdc, { num, 0 });
	}
}

void ImageNumber::SetValue(int value)
{
    text = std::to_string(value);
}
