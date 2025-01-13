#pragma once

#include "WormAction.h"

class WormWalk : public WormAction
{
public:
	WormWalk(Worm* worm);
	~WormWalk();
};