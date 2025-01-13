#include "framework.h"

Button::Button(std::wstring fileName, int typeNumber)
	:ImageRect(fileName, 1, typeNumber)
{
    if (typeNumber > 1)
        isSprite = true;
}

Button::Button(Texture* texture)
	:ImageRect(texture)
{
    isSprite = texture->IsSprite();
}

Button::~Button()
{
}

void Button::Update()
{
    MouseEvent();
}

void Button::Render(HDC hdc)
{
    if (!isSprite)
    {
        ImageRect::Render(hdc);
        return;
    }

    switch (state)
    {
    case Button::NORMAL:
        ImageRect::Render(hdc, { 0, 0 });
        break;
    case Button::OVER:
        ImageRect::Render(hdc, { 0, 1 });
        break;
    case Button::DOWN:
        ImageRect::Render(hdc, { 0, 2 });
        break;
    }
}

bool Button::IsPointCollision(Vector2D mouse)
{
    if (mouse.x < Right() && mouse.x > Left() &&
        mouse.y < Bottom() && mouse.y > Top())
        return true;

    return false;
}

void Button::MouseEvent()
{
    if (IsPointCollision(mousePos))
    {
        state = OVER;

        if (V_KEY->Down(VK_LBUTTON))
            isClick = true;

        if (V_KEY->Press(VK_LBUTTON))
            state = DOWN;

        if (isClick && V_KEY->Up(VK_LBUTTON))
        {
            if (eventHandler)
                eventHandler();

            isClick = false;
        }
    }
    else
    {
        state = NORMAL;

        if (V_KEY->Up(VK_LBUTTON))
            isClick = false;
    }
}
