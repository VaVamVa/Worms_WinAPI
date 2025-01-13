#pragma once

class EffectManager : public Singleton<EffectManager>
{
private:
	typedef std::vector<Effect*> EffectPool;
	typedef std::unordered_map<std::string, EffectPool> EffectsCategory;

private:
	friend Singleton;
	EffectManager();
	~EffectManager();

public:
	void Add(std::string key, UINT poolSize, std::wstring file, int frameX, int frameY,
		float speed = 1.0f, bool loop = false,
		COLORREF transColor = RGB(255, 0, 255));
	void Add(std::string key, UINT poolSize, Texture* texture,
		float speed = 1.0f, bool loop = false);

	void Update();
	void Render(HDC hdc);
	void CamRender(HDC hdc);

	void Play(const std::string& key, const Vector2D pos);

private:
	EffectsCategory effects;
};