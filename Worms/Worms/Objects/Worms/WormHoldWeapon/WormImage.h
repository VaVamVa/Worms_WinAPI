#pragma once

#include "Objects/Worms/WormRender.h"

class WormImage : public WormRender
{
public:
	WormImage(Worm* worm);
	virtual ~WormImage() = default;

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Start(bool isRight) override;

protected:
	ImageRect* image = nullptr;

	POINT curFrame = {};
};