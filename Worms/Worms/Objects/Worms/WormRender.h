#pragma once

#include "Worm.h"

class WormRender
{
private:
    enum Type
    {
        LEFT, RIGHT
    };

public:
    WormRender(Worm* worm) : worm(worm) {}
    virtual ~WormRender() = default;

    virtual void Update() = 0;
    virtual void Render(HDC hdc) = 0;

    virtual void Start(bool isRight) = 0;
    virtual void End() { if (endEvent) endEvent(); }

    virtual void SetStartEvent(Event event) { this->startEvent = event; }
    virtual void SetEndEvent(Event event) { this->endEvent = event; }

protected:
    Worm* worm = nullptr;

    bool isRight = true;

    Event startEvent = nullptr;
    Event endEvent = nullptr;
};