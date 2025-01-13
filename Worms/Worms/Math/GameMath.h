#pragma once

namespace game_math
{
	enum class CardinalPoints
	{
		NONE = 0,
		EAST,
		WEST,
		SOUTH,
		NORTH
	};

	float Clamp(const float& value, const float& min, const float& max);
}