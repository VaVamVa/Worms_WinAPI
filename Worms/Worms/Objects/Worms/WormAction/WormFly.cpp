#include "framework.h"
#include "WormFly.h"

WormFly::WormFly(Worm* worm)
	:WormAction(worm)
{
	action = new ActionObject(L"Resources/Textures/Worm_Fly.bmp", 2, 7);
	action->AddAction(LEFT, 1.0f, false);
	action->GetAction(LEFT)->SetPart(0, 6, false);
	action->AddAction(RIGHT, 1.0f, false);
	action->GetAction(RIGHT)->SetPart(7, 13, false);
	
}

WormFly::~WormFly()
{
	delete action;
}

//void WormFly::Start(bool isRight)
//{
//	isRight ? action->SetAction(RIGHT, true) : action->SetAction(LEFT, true);
//}
