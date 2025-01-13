#include "framework.h"
#include "WormJump.h"

WormJump::WormJump(Worm* worm)
	:WormAction(worm)
{
	action = new ActionObject(L"Resources/Textures/Worm_Jump.bmp", 2, 10);

	action->AddAction(LEFT, 1.0f, false);
	action->GetAction(LEFT)->SetPart(0, 9);

	action->AddAction(RIGHT, 1.0f, false);
	action->GetAction(RIGHT)->SetPart(10, 19);
}

WormJump::~WormJump()
{
	delete action;
}

void WormJump::Start(bool isRight)
{
	isRight ? action->SetAction(RIGHT, true) : action->SetAction(LEFT, true);
}
