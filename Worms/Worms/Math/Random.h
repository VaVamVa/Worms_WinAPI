#pragma once

//
class Random : public Singleton<Random>
{
private:
	friend class Singleton;

	Random();
	~Random();


public:
	// l-value <= return <= r-value
	int GetRandomInt(const int& min, const int& max);
	float GetRandomFloat(const float& min, const float& max);

	POINT GetRandomPosInside(int size = 0);
	POINT GetRandomPosOutside(int size, game_math::CardinalPoints direction);

private:
	std::random_device randDevice;
	std::mt19937_64 engine1;
};