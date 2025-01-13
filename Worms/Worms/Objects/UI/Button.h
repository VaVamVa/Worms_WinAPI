#pragma once

class Button : public ImageRect
{
private:
    enum State
    {
        NORMAL, OVER, DOWN
    };

public:
    Button(std::wstring fileName, int typeNumber = 1);
    Button(Texture* texture);
    ~Button();

    void Update();
    void Render(HDC hdc);

    bool IsPointCollision(Vector2D mouse);

    void SetEvent(Event event) { eventHandler = event; }

private:
    void MouseEvent();

protected:
    State state = NORMAL;

    bool isClick = false;

    Event eventHandler = nullptr;

    bool isSprite = false;
};