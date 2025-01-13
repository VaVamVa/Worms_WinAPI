#include "framework.h"
#include "AimingWeapon.h"

#include "Objects/Bullets/BulletManager.h"

AimingWeapon::AimingWeapon(Worm* worm)
	:WormImage(worm)
{
}

void AimingWeapon::Update()
{
	WormImage::Update();
	WeaponLookAt();
	SetAngle();
	Charging();
}

void AimingWeapon::Render(HDC hdc)
{
	WormImage::Render(hdc);
	Vector2D wormInCam = worm->GetPos() - CAM->GetCamera()->GetPos();

	if (GameManager::DevMode())
	{
		W_TEXT(hdc, static_cast<int>(wormInCam.x) + 15, static_cast<int>(wormInCam.y) - 20, std::to_wstring(angle));
		W_TEXT(hdc, static_cast<int>(wormInCam.x) + 15, static_cast<int>(wormInCam.y) - 5, std::to_wstring(power));
	}
}

void AimingWeapon::Start(bool isRight)
{
	WormImage::Start(isRight);
	angle = isRight ? 0.0f : PI;
	keydownTime = 0.0f;
}

void AimingWeapon::SetAngle()
{
	if (V_KEY->Down(VK_RIGHT))
	{
		if (!isRight)
		{
			isRight = true;
			angle = PI - angle;
			curFrame.x = 1;
		}
	}
	if (V_KEY->Down(VK_LEFT))
	{
		if (isRight)
		{
			isRight = false;
			angle = PI - angle;
			curFrame.x = 0;
		}
	}
}

void AimingWeapon::WeaponLookAt()
{
	// down key 동작으로 angle 변경 가능,
	// down key 동작 수행 시, keydownTime에 0을 할당하여 아래의 조건 충족하게 함.
	if (V_KEY->Down(VK_UP))
	{
		keydownTime = 0.0f;
		LookUp();
	}
	if (V_KEY->Down(VK_DOWN))
	{
		keydownTime = 0.0f;
		LookDown();
	}

	if (keydownTime > 0.0f)
	{
		keydownTime -= DELTA;
		// keydownTime 조건 미충족시, 바로 함수 반환하여 press key 제어.
		return;
	}
	// keydownTime 조건 충족시, keydownTime 초기화 후 press key 상태 관찰.
	keydownTime = AIMING_INTERVAL;

	if (V_KEY->Press(VK_UP))
	{
		LookUp();
	}

	if (V_KEY->Press(VK_DOWN))
	{
		LookDown();
	}
}

void AimingWeapon::LookUp()
{
	switch (isRight)
	{
	case true:
		angle += PI / maxFrame;
		if (angle >= PI * 0.5f)
			angle = PI * 0.5f;
		else
			curFrame.y++;
		break;
	case false:
		angle -= PI / maxFrame;
		if (angle <= PI * 0.5f)
			angle = PI * 0.5f;
		else
			curFrame.y++;

		break;
	}
}

void AimingWeapon::LookDown()
{
	switch (isRight)
	{
	case true:
		angle -= PI / maxFrame;
		if (angle < -PI * 0.5f)
			angle = -PI * 0.5f;
		else if (curFrame.y > 0)
			curFrame.y--;
		break;
	case false:
		angle += PI / maxFrame;
		if (angle > PI * 1.5f)
			angle = PI * 1.5f;
		else if (curFrame.y > 0)
			curFrame.y--;

		break;
	}
}

void AimingWeapon::Charging()
{
	if (CAM->GetTarget() != worm)
	{
		power = MIN_POWER;
		isIncreasing = true;
		isCharging = false;
		return;
	}

	if (isCharging && V_KEY->Up(VK_SPACE))
	{
		BulletManager::Get()->Fire(bulletKey, worm, angle, power);
		return;
	}

	if (V_KEY->Press(VK_SPACE))
	{
		isCharging = true;
		power += isIncreasing ? 0.001f : -0.001f;
		if (power >= MAX_POWER)
			isIncreasing = false;
		else if (power <= MIN_POWER)
			isIncreasing = true;
	}
	if (V_KEY->Down(VK_SPACE))
	{
		power = MIN_POWER;
		isIncreasing = true;
		isCharging = false;
	}

}
