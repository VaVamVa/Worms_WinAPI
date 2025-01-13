#pragma once

class Bullet;

class BulletManager : public Singleton<BulletManager>
{
private:
	friend Singleton;
	BulletManager();
	~BulletManager();

public:
	void Update();
	void Render(HDC hdc);

	bool Fire(std::string key, class Worm* player, float angle = 0.0f, float powerRate = 1.0f);
	void End();

private:
	void LoadTable();
	void CreateBullets(std::vector<std::string>& informations);

private:
	std::unordered_map<std::string, Bullet*> bullets;
	std::unordered_map<std::string, Bullet*>::iterator curBullet;

	Texture* land = nullptr;

	HBRUSH brush = nullptr;
	HPEN pen = nullptr;
};