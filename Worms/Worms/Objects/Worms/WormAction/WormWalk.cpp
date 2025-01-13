#include "framework.h"
#include "WormWalk.h"

WormWalk::WormWalk(Worm* worm)
	:WormAction(worm)
{
	action = new ActionObject(L"Resources/Textures/Worm_Walk.bmp", 2, 15);
	action->AddAction(LEFT, 1.0f, false);
	action->GetAction(LEFT)->SetPart(0, 14, true);
	action->AddAction(RIGHT, 1.0f, false);
	action->GetAction(RIGHT)->SetPart(15, 29, true);
}

WormWalk::~WormWalk()
{
	delete action;
}