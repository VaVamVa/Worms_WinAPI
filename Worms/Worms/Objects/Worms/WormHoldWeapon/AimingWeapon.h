#pragma once

#include "WormImage.h"
#include "Objects/Bullets/Bullet.h"

class AimingWeapon : public WormImage
{
protected:
	const float MAX_POWER = 1.0f;
	const float MIN_POWER = 0.1f;

	const float AIMING_INTERVAL = 0.2f;

public:
	AimingWeapon(Worm* worm);

	virtual void Update() override;
	void Render(HDC hdc) override;

	void Start(bool isRight) override;

protected:
	void SetAngle();

	void WeaponLookAt();
	void LookUp();
	void LookDown();

	void Charging();

protected:
	float maxFrame = 0.0f;

	float angle = 0.0f;
	float keydownTime = 0.0f;

	bool isCharging = false;
	float power = MIN_POWER;
	bool isIncreasing = true;
	std::string bulletKey = "";
};