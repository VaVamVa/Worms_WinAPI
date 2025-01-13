#pragma once

#include "WormAction.h"

class WormJump : public WormAction
{
public:
	WormJump(Worm* worm);
	~WormJump();

	void Start(bool isRight) override;
};