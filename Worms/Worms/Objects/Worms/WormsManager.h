#pragma once

class WormsManager : public Singleton<WormsManager>
{
private:
	const int POOL_SIZE = 5;
	const float ROUND_INTERVAL = 30.0f;
	enum TeamColor
	{
		RED = 0,
		BLUE
	};
	typedef std::map<TeamColor, std::vector<class Worm*>> WormsTeam;

private:
	friend Singleton;
	WormsManager();
	~WormsManager();

public:
	void Update();
	void Render(HDC hdc);

	void Spawn(std::string key, int size);
	std::vector<Worm*> WormInRange(Vector2D pos, float range);
	bool IsCollision(GameObject* other);

	void SetLandTexture(Texture* land) { this->land = land; }
	void SetShotState(bool state);

	const Worm* GetTarget() { return target; }
	Texture* GetLandTexture() { return land; }

private:
	void CreateTeamContainers();
	void CreateTeamColor();

	void LoadTable(std::string key);

	void SwapTarget();

	void EndGame();

private:
	WormsTeam wormsTeam;
	int teamCount[2];

	std::vector<Vector2D> spawnPositions;

	Texture* land;
	Worm* target = nullptr;

	ActionObject* teamColor[2];

	bool isShootingPhase = false;
	float roundTime = 0.0f;
	TeamColor curTeam = RED;
	int curWormIndex = 0;
	int poolSize;

	Worm* dieWorm = nullptr;
};