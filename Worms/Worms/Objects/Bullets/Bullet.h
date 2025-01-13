#pragma once

#include "Objects/Worms/Worm.h"

class Bullet : public GameObject
{
private:
	const float GRAVITY = 0.98f;

public:
	Bullet(float firingForce, float pushPower, float range, float damage);
	virtual ~Bullet();

	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Fire(Worm* player, float angle, float powerRate);

	void End();

protected:
	void Bomb();

protected:
	Texture* land = nullptr;
	Effect* endEffect = nullptr;

	Vector2D velocity;
	float firingForce;
	float pushPower;
	float range;
	float damage;

	bool isShot = false;

	int bombLeft = 0;
	int bombRight = 0;
	int bombTop = 0;
	int bombBottom = 0;

	HPEN pen;
};