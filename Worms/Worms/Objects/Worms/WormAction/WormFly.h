#pragma once

#include "WormAction.h"

class WormFly : public WormAction
{
public:
	WormFly(Worm* worm);
	~WormFly();

	//void Start(bool isRight) override;
};