#include "framework.h"

float game_math::Clamp(const float& value, const float& min, const float& max)
{
	if (value > max)
		return max;

	if (value < min)
		return min;

	return value;
}