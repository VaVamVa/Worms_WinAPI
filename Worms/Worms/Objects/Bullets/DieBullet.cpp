#include "framework.h"
#include "Bullet.h"
#include "DieBullet.h"

DieBullet::DieBullet(float firingForce, float pushPower, float range, float damage)
	:Bullet(firingForce, pushPower, range, damage)
{
	range = 30.0f;
	damage = 50.0f;

	// change resource
	endEffect = new Effect(L"Resources/Textures/Etc/FireHit.bmp", 1, 9, 1.0f, false, RGB(192, 192, 128));
	endEffect->SetEndEvent(std::bind(&Bullet::End, this));
}

DieBullet::~DieBullet()
{
	delete endEffect;
}

void DieBullet::Fire(Worm* player, float angle, float powerRate)
{
	Bullet::Fire(player, angle, powerRate);
	this->pos = player->GetPos();
	Bomb();
}
