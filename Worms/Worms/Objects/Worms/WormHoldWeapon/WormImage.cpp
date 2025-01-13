#include "framework.h"
#include "WormImage.h"

WormImage::WormImage(Worm* worm)
	:WormRender(worm)
{
}

void WormImage::Update()
{
	image->SetPos(worm->GetPos());
}

void WormImage::Render(HDC hdc)
{
	image->CamRender(hdc, curFrame);
}

void WormImage::Start(bool isRight)
{
	if (startEvent)
		startEvent();
	curFrame.x = isRight ? 1 : 0;
	curFrame.y = image->GetTexture()->GetFrame().y >> 1;
	this->isRight = isRight;
}
