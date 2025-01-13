#pragma once

class WormRender;

class Worm : public GameObject
{
private:
    enum State
    {
        IDLE, WALK, JUMP, LAND, FLY, DIE,
        NONE = 16,
        HOLD_CANNON = 32, HOLD_GRANADE
    };

    const float GRAVITY = 1.98f;
    const float MOVE_SPEED = 100.f;
    const float JUMP_POWER = -0.98f;
    const float MAX_JUMP_POWER = -500.0f;
    const float SLOP = 10.0f;
    const float PUSH_LAND = 1.0f;
    const int MAX_HP = 10;

public:
    Worm();
    ~Worm();

    void Update();
    void Render(HDC hdc);

    void SetLandTexture(Texture* land) { this->land = land; }

    void SetLookAt(bool isRight) { this->isRight = isRight; }

    void Spawn(Vector2D pos);
    
    void Damage(float power);
    bool IsDie() { return curHp == 0; }
    void SetDie();

private:
    bool BlockedByWall();

    void Move();
    void Jump();
    void Gravity();

    void HoldWeapon();

    void FlyUp();
    void Landing();
    void StopMoving();
    void StopAction();
    void Die();

    void CreateActions();
    void CreateHoldWeapons();

    void SetAction(State state);

private:
    std::map<State, WormRender*> renders;

    int curHp = 0;
    Vector2D velocity;

    Texture* land = nullptr;

    State curState = NONE;

    bool isRight = true;

    bool isJump = false;
    float jumpPower = 0.0f;
};