#include "framework.h"

Random::Random()
	:engine1(randDevice())
{
}

Random::~Random()
{
}

int Random::GetRandomInt(const int& min, const int& max)
{
	std::uniform_int_distribution<int> range(min, max);
	return range(engine1);
}

float Random::GetRandomFloat(const float& min, const float& max)
{
	std::uniform_real_distribution<float> range(0, 1);
	return (max - min) * range(engine1) + min;
}

POINT Random::GetRandomPosInside(int size)
{
	if (size > CLIENT_HEIGHT || size > CLIENT_WIDTH)
		return { CLIENT_WIDTH >> 1, CLIENT_HEIGHT >> 1 };
	std::uniform_int_distribution<int> xRange(size, CLIENT_WIDTH - size);
	int x = xRange(engine1);
	std::uniform_int_distribution<int> yRange(size, CLIENT_HEIGHT - size);
	int y = yRange(engine1);

	return { x, y };
}

POINT Random::GetRandomPosOutside(int size, game_math::CardinalPoints direction)
{
	if (direction == game_math::CardinalPoints::NONE)
	{
		std::uniform_int_distribution<int> range(1, 4);
		direction = (game_math::CardinalPoints)range(engine1);
	}
	else
		direction = (game_math::CardinalPoints)direction;

	int x = 0;
	int y = 0;
	switch (direction)
	{
	case game_math::CardinalPoints::EAST:
	{
		x = CLIENT_WIDTH + size;
		std::uniform_int_distribution<int> range(size , CLIENT_HEIGHT - size);
		y = range(engine1);
	}
		break;
	case game_math::CardinalPoints::WEST:
	{
		x = -size;
		std::uniform_int_distribution<int> range(size, CLIENT_HEIGHT - size);
		y = range(engine1);
	}
		break;
	case game_math::CardinalPoints::SOUTH:
	{
		std::uniform_int_distribution<int> range(size, CLIENT_WIDTH - size);
		x = range(engine1);
		y = CLIENT_HEIGHT + size;
	}
		break;
	case game_math::CardinalPoints::NORTH:
	{
		std::uniform_int_distribution<int> range(size, CLIENT_WIDTH - size);
		x = range(engine1);
		y = -size;
	}
		break;

	}

	return { x, y };
}
