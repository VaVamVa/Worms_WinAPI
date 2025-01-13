#include "framework.h"
#include "Objects/Worms/WormsManager.h"
#include "BulletManager.h"

#include "CannonBullet.h"
#include "DieBullet.h"

BulletManager::BulletManager()
{
	curBullet = bullets.end();

	LoadTable();

	land = WormsManager::Get()->GetLandTexture();

	brush = CreateSolidBrush(land->GetTransparentColor());
	pen = CreatePen(PS_SOLID, 0, land->GetTransparentColor());
}

BulletManager::~BulletManager()
{
	FOR_OBJ(bullets)
		delete iter.second;
	bullets.clear();

	DeleteObject(brush);
	DeleteObject(pen);
}

void BulletManager::Update()
{
	if (curBullet != bullets.end())
		curBullet->second->Update();
}

void BulletManager::Render(HDC hdc)
{
	SelectObject(land->GetMemDC(), brush);
	SelectObject(land->GetMemDC(), pen);
	if (curBullet != bullets.end())
		curBullet->second->Render(hdc);
}

bool BulletManager::Fire(std::string key, Worm* player, float angle, float powerRate)
{
	curBullet = bullets.find(key);
	if (curBullet == bullets.end())
		return false;
	curBullet->second->Fire(player, angle, powerRate);
	return true;
}

void BulletManager::End()
{
	curBullet = bullets.end();
}

void BulletManager::LoadTable()
{
	std::string fileName = "DataTable/Worm_Weapons.csv";
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

	std::vector<std::string> informations(5);
	while (true)
	{
		std::getline(file, oneLine);
		std::istringstream split(oneLine);

		if (oneLine == "")
			break;

		int i = 0;
		for (std::string digit; std::getline(split, digit, ','); i++)
		{
			informations[i] = digit;
		}
		CreateBullets(informations);

		if (file.eof())
			break;
	}
}

void BulletManager::CreateBullets(std::vector<std::string>& informations)
{
	float firingForce = std::stof(informations[1]);
	float pushPower = std::stof(informations[2]);
	float range = std::stof(informations[3]);
	float damage = std::stof(informations[4]);

	if (informations[0] == "Cannon")
		bullets[informations[0]] = new CannonBullet(firingForce, pushPower, range, damage);
	else if (informations[0] == "Die")
		bullets[informations[0]] = new DieBullet(firingForce, pushPower, range, damage);
	
}

