#include "framework.h"
#include "Objects/Bullets/CannonBullet.h"
#include "WormCannon.h"

WormCannon::WormCannon(Worm* worm)
	:AimingWeapon(worm)
{
	image = new ImageRect(L"Resources/Textures/Worm_Cannon.bmp", 2, 32);
	maxFrame = static_cast<float>(image->GetTexture()->GetFrame().y);
	bulletKey = "Cannon";
}

WormCannon::~WormCannon()
{
	delete image;
}