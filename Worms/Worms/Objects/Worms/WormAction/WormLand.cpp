#include "framework.h"
#include "WormAction.h"
#include "WormLand.h"

WormLand::WormLand(Worm* worm)
	:WormAction(worm)
{
	action = new ActionObject(L"Resources/Textures/Worm_Jump.bmp", 2, 10);

	action->AddAction(LEFT, 1.0f, false);
	action->GetAction(LEFT)->SetPart(9, 0);
	action->GetAction(LEFT)->SetEndEvent(std::bind(&WormLand::End, this));

	action->AddAction(RIGHT, 1.0f, false);
	action->GetAction(RIGHT)->SetPart(19, 10);
	action->GetAction(RIGHT)->SetEndEvent(std::bind(&WormLand::End, this));
}

WormLand::~WormLand()
{
	delete action;
}

void WormLand::Start(bool isRight)
{
	if (startEvent)
		startEvent();
	isRight ? action->SetAction(RIGHT, true) : action->SetAction(LEFT, true);
}
