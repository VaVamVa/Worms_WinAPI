#include "framework.h"
#include "WormAction.h"

WormAction::WormAction(Worm* worm)
	:WormRender(worm)
{
}

void WormAction::Update()
{
	action->Update();
}

void WormAction::Render(HDC hdc)
{
	action->SetPos(worm->GetPos());
	action->CamRender(hdc);
}