#include "framework.h"
#include "Worm.h"
#include "WormsManager.h"

WormsManager::WormsManager()
{
	CreateTeamContainers();
	CreateTeamColor();
}

WormsManager::~WormsManager()
{
	FOR_OBJ(wormsTeam)
	{
		for (Worm* worm : iter.second)
		{
			if (worm != nullptr)
				delete worm;
		}
	}
	wormsTeam.clear();
}

void WormsManager::Update()
{
	teamCount[RED] = 0;
	teamCount[BLUE] = 0;
	FOR(i, 0, 2)
		teamColor[i]->Update();

	// define FOR_OBJ(Iters) for(auto& iter : Iters)
	FOR_OBJ(wormsTeam)
	{
		for (Worm* worm : iter.second)
		{
			if (worm != nullptr && worm->IsActive())
			{
				teamCount[iter.first]++;
				worm->Update();

				if (dieWorm == nullptr && worm->IsDie())
				{
					dieWorm = worm;
				}
			}
		}
	}
	
	if (!isShootingPhase)
	{
		if (dieWorm != nullptr)
		{
			dieWorm->SetDie();
			return;
		}
		EndGame();

		if (roundTime > 0.0f)
			roundTime -= DELTA;
		else
		{
			SwapTarget();
		}
	}
}

void WormsManager::Render(HDC hdc)
{
	TeamColor targetColor;
	FOR_OBJ(wormsTeam)
	{
		for (Worm* worm : iter.second)
		{
			if (worm != nullptr && worm->IsActive())
			{
				if (target == worm)
				{
					targetColor = iter.first;
					continue;
				}
				worm->Render(hdc);
				teamColor[iter.first]->SetPos(worm->GetPos().x, worm->Top() - worm->GetSize().y);
				teamColor[iter.first]->CamRender(hdc);
			}
		}
	}
	if (target->IsActive())
	{
		target->Render(hdc);
		teamColor[targetColor]->SetPos(target->GetPos().x, target->Top() - target->GetSize().y);
		teamColor[targetColor]->CamRender(hdc);
	}

	if (!isShootingPhase)
		W_TEXT(hdc, CLIENT_WIDTH >> 1, 30, std::to_wstring(static_cast<int>(roundTime)));
}

void WormsManager::Spawn(std::string key, int size)
{
	if (size > POOL_SIZE)
		poolSize = POOL_SIZE;
	else
		poolSize = size;

	LoadTable(key);
	curWormIndex = 0;
	curTeam = RED;

	int index = 0;
	FOR_OBJ(wormsTeam)
	{
		FOR(i, 0, poolSize)
		{
			if (iter.second[i] == nullptr)
				iter.second[i] = new Worm();
			iter.second[i]->Spawn(spawnPositions[index]);
			index++;
		}
	}
	target = wormsTeam[curTeam][curWormIndex];
	CAM->SetTarget(target);
	FOR_OBJ(wormsTeam)
	{
		for (Worm* worm : iter.second)
		{
			if (worm != nullptr && worm->IsActive())
				worm->Update();
		}
	}
}

std::vector<Worm*> WormsManager::WormInRange(Vector2D pos, float range)
{
	std::vector<Worm*> result;
	FOR_OBJ(wormsTeam)
	{
		for (Worm* worm : iter.second)
		{
			if (worm != nullptr && worm->IsActive())
				if (worm->IsCollision(pos, Vector2D(range, 0.0f)))
				{
					result.push_back(worm);
				}
		}
	}
	return result;
}

bool WormsManager::IsCollision(GameObject* other)
{
	FOR_OBJ(wormsTeam)
	{
		for (Worm* worm : iter.second)
		{
			if (worm != nullptr && worm->IsActive())
				if (worm->IsCollision(other))
				{
					return true;
				}
		}
	}
	return false;
}

void WormsManager::SetShotState(bool state)
{
	isShootingPhase = state;
	if (state)
	{
		roundTime = 0.0f;
	}
	else
		dieWorm = nullptr;
}

void WormsManager::SwapTarget()
{
	if (curTeam == RED)
		curTeam = BLUE;
	else
	{
		curTeam = RED;
		curWormIndex = curWormIndex + 1 < poolSize ? curWormIndex + 1 : 0;
	}

	if (wormsTeam[curTeam][curWormIndex]->IsActive())
	{
		roundTime = ROUND_INTERVAL;
		target = wormsTeam[curTeam][curWormIndex];
		CAM->SetTarget(target);
	}
	else
	{
		roundTime = 0.0f;
	}
}

void WormsManager::EndGame()
{
	if (teamCount[RED] == 0 && teamCount[BLUE] == 0)
		SceneManager::Get()->ChangeScene("End", "Draw");
	else if (teamCount[RED] == 0)
		SceneManager::Get()->ChangeScene("End", "Blue");
	else if (teamCount[BLUE] == 0)
		SceneManager::Get()->ChangeScene("End", "Red");
}

void WormsManager::CreateTeamContainers()
{
	std::vector<Worm*> redWorms(POOL_SIZE, nullptr);
	std::vector<Worm*> blueWorms(POOL_SIZE, nullptr);
	wormsTeam.insert({ RED, redWorms });
	wormsTeam.insert({ BLUE, blueWorms });
}

void WormsManager::CreateTeamColor()
{
	teamColor[RED] = new ActionObject(L"Resources/Textures/Etc/ArrowDown_Red.bmp", 1, 30, RGB(128, 128, 192));
	teamColor[RED]->AddAction(RED, 2.0f, false);
	teamColor[RED]->GetAction(RED)->SetDefault(true);
	teamColor[RED]->SetAction(RED);
	teamColor[BLUE] = new ActionObject(L"Resources/Textures/Etc/ArrowDown_Blue.bmp", 1, 30, RGB(64, 64, 128));
	teamColor[BLUE]->AddAction(BLUE, 2.0f, false);
	teamColor[BLUE]->GetAction(BLUE)->SetDefault(true);
	teamColor[BLUE]->SetAction(BLUE);
}

void WormsManager::LoadTable(std::string key)
{
    std::string fileName = "DataTable/Worm_Land_" + key + ".csv";
    std::ifstream file;

	try
	{
		file.open(fileName, std::ios::in);
		if (file.fail()) throw std::runtime_error{ " Unable to open file " };
	}
	catch (const std::string e)
	{
		::OutputDebugStringA(e.c_str());
		file.close();
		return;
	}

	std::string oneLine = "";
	std::getline(file, oneLine);
	std::istringstream split(oneLine);
	int col = 0;
	for (std::string digit; std::getline(split, digit, ','); col++)
		if (col > POOL_SIZE)
			return;

	spawnPositions.clear();

    while (true)
    {
		std::getline(file, oneLine);
		std::istringstream split(oneLine);
		std::string datas[3];
		int i = 0;
		for (std::string digit; std::getline(split, digit, ',');)
		{
			datas[i] = digit;
			i++;
		}
		spawnPositions.push_back(Vector2D(std::stof(datas[1]), std::stof(datas[2])));

        if (file.eof())
            break;
    }
	int randomForward = 0, randomBackward = 0;
	FOR(i, 0, spawnPositions.size() * 2)
	{
		randomForward = RANDOM->GetRandomInt(0, static_cast<int>(spawnPositions.size() - 1));
		randomBackward = RANDOM->GetRandomInt(0, static_cast<int>(spawnPositions.size() - 1));
		Vector2D tmp = spawnPositions[randomForward];
		spawnPositions[randomForward] = spawnPositions[randomBackward];
		spawnPositions[randomBackward] = tmp;

	}

	file.close();
}
