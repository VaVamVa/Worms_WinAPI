#include "framework.h"
#include "CannonBullet.h"

CannonBullet::CannonBullet(float firingForce, float pushPower, float range, float damage)
	:Bullet(firingForce, pushPower, range, damage)
{
	image = new ActionObject(L"Resources/Textures/Weapon/Fire.bmp", 4, 1);
	image->AddAction(0);
	image->GetAction(0)->SetDefault(true);
	image->SetAction(0);
	image->SetImageToObjectSize(this);
	this->size.y = 0.0f;

	endEffect = new Effect(L"Resources/Textures/Etc/FireHit.bmp", 1, 9, 1.0f, false, RGB(192, 192, 128));
	endEffect->SetEndEvent(std::bind(&Bullet::End, this));

	
}

CannonBullet::~CannonBullet()
{
	delete image;
	delete endEffect;
}

void CannonBullet::Update()
{
	if (!active)
		return;

	image->SetPos(pos);
	image->Update();
	Bullet::Update();
}

void CannonBullet::Render(HDC hdc)
{
	if (!active)
		return;
	Bullet::Render(hdc);
	if (endEffect->IsActive())
		return;
	image->CamRender(hdc);
}
