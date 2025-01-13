#include "framework.h"
#include "WormIdle.h"

WormIdle::WormIdle(Worm* worm)
	:WormAction(worm)
{
	action = new ActionObject(L"Resources/Textures/Worm_Idle.bmp", 2, 18);
	action->AddAction(LEFT, 1.0f, false);
	action->GetAction(LEFT)->SetPart(0, 17, true);
	action->AddAction(RIGHT, 1.0f, false);
	action->GetAction(RIGHT)->SetPart(18, 35, true);

	action->SetImageToObjectSize(worm);
}

WormIdle::~WormIdle()
{
	delete action;
}

void WormIdle::Start(bool isRight)
{
	startEvent();
	WormAction::Start(isRight);
}
