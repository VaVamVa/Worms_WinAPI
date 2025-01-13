#include "framework.h"

Effect::Effect(std::wstring file, int frameX, int frameY, float speed, bool loop, COLORREF transColor)
    : ImageRect(file, frameX, frameY, transColor)
{
    animation = new Animation(maxFrame, speed);
    animation->SetDefault(loop);
    animation->SetEndEvent(std::bind(&Effect::Stop, this));
}

Effect::Effect(Texture* texture, float speed, bool loop)
    : ImageRect(texture)
{
    animation = new Animation(maxFrame, speed);
    animation->SetDefault(loop);
    animation->SetEndEvent(std::bind(&Effect::Stop, this));
}

Effect::~Effect()
{
    delete animation;
}

void Effect::Update()
{
    if (!active) return;

    animation->Update();
}

void Effect::Render(HDC hdc)
{
    if (!active) return;
    ImageRect::Render(hdc, animation->GetFrame());
}

void Effect::CamRender(HDC hdc)
{
    if (!active) return;
    
    ImageRect::CamRender(hdc, animation->GetFrame());
}

void Effect::Play(const Vector2D& pos)
{
    active = true;

    this->pos = pos;
    animation->Play();
}

void Effect::Stop()
{
    active = false;
    if (endEvent)
        endEvent();
}