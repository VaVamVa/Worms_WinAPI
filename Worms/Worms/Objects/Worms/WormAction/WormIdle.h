#pragma once

#include "WormAction.h"

class WormIdle : public WormAction
{
public:
	WormIdle(Worm* worm);
	~WormIdle();

	void Start(bool isRight) override;
};