#include "framework.h"
#include "Bullet.h"

#include "BulletManager.h"
#include "Objects/Worms/WormsManager.h"

Bullet::Bullet(float firingForce, float pushPower, float range, float damage)
    :firingForce(firingForce), pushPower(pushPower), range(range), damage(damage)
{
    land = WormsManager::Get()->GetLandTexture();
    pen = CreatePen(PS_DASHDOT, 1, RGB(0, 255, 0));
}

Bullet::~Bullet()
{
    DeleteObject(pen);
}

void Bullet::Update()
{
    if (!active) return;
    if (endEffect && endEffect->IsActive())
    {
        endEffect->Update();
        return;
    }
    GameObject::Update();
    if (land->GetEffectivePixelUnderPosY(pos) < bottom || WormsManager::Get()->IsCollision(this))
    {
        Bomb();
        return;
    }
    velocity.y += GRAVITY;
    Translate(velocity);
}

void Bullet::Render(HDC hdc)
{
    if (GameManager::DevMode())
    {
        GameObject::CamRender(hdc);
    }
    if (endEffect && endEffect->IsActive())
    {
        endEffect->CamRender(hdc);
        if (GameManager::DevMode())
        {
            HPEN defaultPen = (HPEN)SelectObject(hdc, pen);
            HBRUSH defaultBrush = (HBRUSH)SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));

            Ellipse(hdc, bombLeft - CAM->GetCamera()->GetPos().x, bombTop - CAM->GetCamera()->GetPos().y, bombRight - CAM->GetCamera()->GetPos().x, bombBottom - CAM->GetCamera()->GetPos().y);
            SelectObject(hdc, defaultPen);
            SelectObject(hdc, defaultBrush);
        }
        return;
    }
}

void Bullet::Fire(Worm* player, float angle, float powerRate)
{
    active = true;
    isShot = false;
    velocity = { cos(angle), -sin(angle) };
    this->pos = player->GetPos() + velocity * max(player->GetSize().y, player->GetSize().x);
    velocity *= powerRate * firingForce;
    CAM->SetTarget(this);
    WormsManager::Get()->SetShotState(true);
}

void Bullet::End()
{
    WormsManager::Get()->SetShotState(false);
    active = false;
    BulletManager::Get()->End();
}

void Bullet::Bomb()
{
    bombLeft = static_cast<int>(pos.x - this->range);
    bombRight = static_cast<int>(pos.x + this->range);
    bombTop = static_cast<int>(pos.y - this->range);
    bombBottom = static_cast<int>(pos.y + this->range);

    Ellipse(land->GetMemDC(), bombLeft, bombTop, bombRight, bombBottom);
    FOR_OBJ(WormsManager::Get()->WormInRange(this->pos, range))
    {
        float damagedRatio = (1.0f - (iter->GetPos() - pos).Length() / range);
        iter->Damage(damagedRatio * damage);
        // iter->Push(ratio * pushPower);
    }

    if (endEffect)
        endEffect->Play(pos);
    else
        End();
}
