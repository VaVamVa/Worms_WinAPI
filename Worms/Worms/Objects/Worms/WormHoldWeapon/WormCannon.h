#pragma once

#include "AimingWeapon.h"

class WormCannon : public AimingWeapon
{
public:
	WormCannon(Worm* worm);
	~WormCannon();
};