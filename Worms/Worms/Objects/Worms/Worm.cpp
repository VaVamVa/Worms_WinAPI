#include "framework.h"

#include "WormAction/WormIdle.h"
#include "WormAction/WormWalk.h"
#include "WormAction/WormJump.h"
#include "WormAction/WormFly.h"
#include "WormAction/WormLand.h"
#include "WormAction/WormDie.h"

#include "WormHoldWeapon/WormCannon.h"

#include "Objects/Bullets/BulletManager.h"

#include "Worm.h"
#include "WormsManager.h"

Worm::Worm()
{
	CreateActions();
	CreateHoldWeapons();
}

Worm::~Worm()
{
	FOR_OBJ(renders)
	{
		delete iter.second;
	}
}

void Worm::Update()
{
	if (!active)
		return;

	GameObject::Update();
	renders[curState]->Update();

	if (curState == DIE)
		return;

	Translate(velocity);

	Gravity();
	
	if (WormsManager::Get()->GetTarget() == this)
	{
		if (curState != FLY)
			HoldWeapon();

		if (curState < NONE)
		{
			Move();
			Jump();
		}
	}
	else if (curState > NONE)
		renders[curState]->End();

	if (static_cast<int>(bottom) >= land->GetImageSize().cy)
		curHp = 0;
}

void Worm::Render(HDC hdc)
{
	if (curState == NONE || !active)
		return;
	renders[curState]->Render(hdc);
	if (GameManager::DevMode())
	{
		GameObject::CamRender(hdc);
		W_TEXT(hdc, static_cast<int>(pos.x - size.x - CAM->GetCamera()->GetPos().x) - 5, static_cast<int>(top - CAM->GetCamera()->GetPos().y - 20), std::to_wstring(curHp));
	}
}

void Worm::Spawn(Vector2D pos)
{
	isRight = RANDOM->GetRandomInt(0, 1);
	SetAction(IDLE);

	land = WormsManager::Get()->GetLandTexture();

	this->pos = pos;
	active = true;
	curHp = MAX_HP;
}

void Worm::Damage(float power)
{
	if (power < 0.0f)
		return;
	curHp -= static_cast<int>(power);
	if (curHp <= 0)
	{
		curHp = 0;
	}
}

void Worm::SetDie()
{
	if (CAM->GetTarget() != this) CAM->SetTarget(this);
	SetAction(DIE);
}

bool Worm::BlockedByWall()
{
	if (velocity.x == 0.0f)
		return true;
	float nextSide = velocity.x > 0.0f ? right : left;
	
	return (bottom - land->GetEffectivePixelUnderPosY({nextSide, pos.y}) < SLOP);
}

void Worm::Move()
{
	if (curState == JUMP || curState == LAND || curState == FLY) return;

	bool isMove = false;

	if (V_KEY->Press(VK_RIGHT) && V_KEY->Press(VK_LEFT))
		isMove = false;
	else if (V_KEY->Press(VK_RIGHT))
	{
		isRight = true;
		isMove = true;
	}
	else if (V_KEY->Press(VK_LEFT))
	{
		isRight = false;
		isMove = true;
	}

	if (isMove)
	{
		SetAction(WALK);
		if (!BlockedByWall())
		{
			velocity.x = 0.0f;
			pos.x += isRight ? -PUSH_LAND : PUSH_LAND;
		}
		else
		{
			velocity.x = isRight ? MOVE_SPEED : -MOVE_SPEED;
			
			float nextSide = isRight ? right : left;
			float slop = land->GetEffectivePixelUnderPosY({ nextSide, pos.y }) - bottom;

			if (slop < 0 && slop > -SLOP)
				velocity.y += slop;
			else if (slop > 0 && slop < SLOP)
				velocity.y += slop;
		}
	}
	else
	{
		SetAction(IDLE);
	}
}

void Worm::Jump()
{
	if (curState == FLY || curState == LAND) return;
	
	if (isJump == false && V_KEY->Down(VK_UP))
	{
		isJump = true;
		SetAction(JUMP);
		velocity.x = 0.0f;
	}
	if (V_KEY->Press(VK_UP))
	{
		jumpPower += JUMP_POWER;
		if (jumpPower < MAX_JUMP_POWER)
			jumpPower = MAX_JUMP_POWER;
	}
	if (V_KEY->Up(VK_UP))
	{
		renders[curState]->End();
	}
}

void Worm::Gravity()
{
	int stepOn = land->IsEffectivePixelPosY(Vector2D(pos.x, bottom))
		+ land->IsEffectivePixelPosY(Vector2D(right, bottom))
		+ land->IsEffectivePixelPosY(Vector2D(left, bottom));
	float midLand = land->GetEffectivePixelUnderPosY(pos);

	if (stepOn < 2)
	{
		if (midLand - bottom > SLOP)
		{
			velocity.y += GRAVITY;
			SetAction(FLY);
		}
		if (!BlockedByWall())
			velocity.x = -velocity.x;
		if (land->IsEffectivePixelPosY(Vector2D(pos.x, top)))
		{
			velocity.y = abs(velocity.y);
		}
	}
	else if (curState != JUMP && abs(velocity.y) > 0.0f)
	{
		velocity.y = 0.0f;
		if (curState == FLY)
			renders[curState]->End();
		jumpPower = 0.0f;
		if (land->IsEffectivePixelPosY(Vector2D(pos.x, bottom)))
		{
			pos.y = midLand - size.y * 0.5f;
		}
	}
}

void Worm::HoldWeapon()
{
	if (curState == JUMP || curState == LAND) return;
	if (V_KEY->Down('1'))
		curState == HOLD_CANNON ? SetAction(IDLE) : SetAction(HOLD_CANNON);
	
	if (curState > NONE)
	{
		if (!isRight && V_KEY->Down(VK_RIGHT))
			isRight = true;
		else if (isRight && V_KEY->Down(VK_LEFT))
			isRight = false;
	}
}

void Worm::FlyUp()
{
	velocity.x = isRight ? MOVE_SPEED : -MOVE_SPEED;
	velocity.y = jumpPower;
	isJump = false;
	pos.y--;
	SetAction(FLY);
	jumpPower = 0.0f;
}

void Worm::Landing()
{
	SetAction(LAND);  // Lading
}

void Worm::StopMoving()
{
	velocity = Vector2D();
}

void Worm::StopAction()
{
	SetAction(IDLE);
}

void Worm::Die()
{
	active = false;
	BulletManager::Get()->Fire("Die", this, 0.0f, 1.0f);
}


void Worm::CreateActions()
{
	renders[IDLE] = new WormIdle(this);
	renders[WALK] = new WormWalk(this);
	renders[JUMP] = new WormJump(this);
	renders[FLY] = new WormFly(this);
	renders[LAND] = new WormLand(this);
	renders[DIE] = new WormDie(this);

	renders[IDLE]->SetStartEvent(std::bind(&Worm::StopMoving, this));

	renders[JUMP]->SetEndEvent(std::bind(&Worm::FlyUp, this));

	renders[FLY]->SetEndEvent(std::bind(&Worm::Landing, this));

	renders[LAND]->SetStartEvent(std::bind(&Worm::StopMoving, this));
	renders[LAND]->SetEndEvent(std::bind(&Worm::StopAction, this));

	renders[DIE]->SetEndEvent(std::bind(&Worm::Die, this));
}

void Worm::CreateHoldWeapons()
{
	renders[HOLD_CANNON] = new WormCannon(this);
	renders[HOLD_CANNON]->SetStartEvent(std::bind(&Worm::StopMoving, this));
	renders[HOLD_CANNON]->SetEndEvent(std::bind(&Worm::StopAction, this));
}

void Worm::SetAction(State state)
{
	if (curState == state) return;

	curState = state;
	renders[state]->Start(isRight);
}
