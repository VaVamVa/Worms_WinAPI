#include "framework.h"
#include "WormAction.h"
#include "WormDie.h"

WormDie::WormDie(Worm* worm)
	:WormAction(worm)
{
	// change resource
	action = new ActionObject(L"Resources/Textures/Worm_Jump.bmp", 2, 10);

	action->AddAction(LEFT, 1.0f, false);
	action->GetAction(LEFT)->SetPart(9, 0);
	action->GetAction(LEFT)->SetEndEvent(std::bind(&WormDie::End, this));

	action->AddAction(RIGHT, 1.0f, false);
	action->GetAction(RIGHT)->SetPart(19, 10);
	action->GetAction(RIGHT)->SetEndEvent(std::bind(&WormDie::End, this));
}

WormDie::~WormDie()
{
	delete action;
}

void WormDie::Start(bool isRight)
{
	isRight ? action->SetAction(RIGHT, true) : action->SetAction(LEFT, true);
}
