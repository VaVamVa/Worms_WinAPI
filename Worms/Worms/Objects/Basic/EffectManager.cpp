#include "framework.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
    FOR_OBJ(effects)
    {
        for (Effect* effect : iter.second)
        {
            delete effect;
        }
    }
    effects.clear();
}

void EffectManager::Add(std::string key, UINT poolSize, std::wstring file, int frameX, int frameY, float speed, bool loop, COLORREF transColor)
{
    if (effects.count(key) > 0) return;

    Texture* texture = Texture::Add(file, frameX, frameY, transColor);

    EffectPool effectPool(poolSize, nullptr);

    for (Effect*& effect : effectPool)
    {
        effect = new Effect(texture, speed, loop);
    }

    effects[key] = effectPool;
}

void EffectManager::Add(std::string key, UINT poolSize, Texture* texture, float speed , bool loop)
{
    if (effects.count(key) > 0) return;

    EffectPool effectPool(poolSize, nullptr);

    for (Effect*& effect : effectPool)
    {
        effect = new Effect(texture, speed, loop);
    }

    effects[key] = effectPool;
}

void EffectManager::Update()
{
    FOR_OBJ(effects)
    {
        for (Effect* effect : iter.second)
        {
            effect->Update();
        }
    }
}

void EffectManager::Render(HDC hdc)
{
    FOR_OBJ(effects)
    {
        for (Effect* effect : iter.second)
        {
            effect->Render(hdc);
        }
    }
}

void EffectManager::CamRender(HDC hdc)
{
    FOR_OBJ(effects)
    {
        for (Effect* effect : iter.second)
        {
            effect->CamRender(hdc);
        }
    }
}

void EffectManager::Play(const std::string& key, const Vector2D pos)
{
    for (Effect* effect : effects[key])
    {
        if (!effect->IsActive())
        {
            effect->Play(pos);
            return;
        }
    }
}