#pragma once

class DieBullet : public Bullet
{
public:
	DieBullet(float firingForce, float pushPower, float range, float damage);
	~DieBullet();

	void Fire(Worm* player, float angle, float powerRate) override;
};