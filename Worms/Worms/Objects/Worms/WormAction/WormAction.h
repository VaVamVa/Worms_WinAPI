#pragma once

#include "../WormRender.h"

class WormAction : public WormRender
{
protected:

    enum Type
    {
        LEFT, RIGHT
    };

public:
    WormAction(Worm* worm);
    virtual ~WormAction() {}

    virtual void Update();
    virtual void Render(HDC hdc);

    virtual void Start(bool isRight) { isRight ? action->SetAction(RIGHT) : action->SetAction(LEFT); }

protected:
    ActionObject* action = nullptr;

};