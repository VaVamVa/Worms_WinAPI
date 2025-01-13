#pragma once

#include "Bullet.h"

class CannonBullet : public Bullet
{
public:
	CannonBullet(float shotPower, float pushPower, float range, float damage);
	~CannonBullet();

	// Bullet을(를) 통해 상속됨
	void Update() override;
	void Render(HDC hdc) override;

private:
	ActionObject* image = nullptr;
};