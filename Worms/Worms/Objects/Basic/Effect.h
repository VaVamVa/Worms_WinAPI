#pragma once

class Effect : public ImageRect
{
public:
public:
    Effect(std::wstring file, int frameX, int frameY, float speed = 1.0f,
        bool loop = false, COLORREF transColor = RGB(255, 0, 255));
    Effect(Texture* texture, float speed = 1.0f, bool loop = false);
    ~Effect();

    void Update();
    void Render(HDC hdc);
    void CamRender(HDC hdc);

    void Play(const Vector2D& pos);
    void Stop();

    void SetEndEvent(Event event) { endEvent = event; }

private:
    Animation* animation;
    Event endEvent = nullptr;
};