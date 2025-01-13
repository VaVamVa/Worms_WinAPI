#pragma once

struct Vector2D
{
	float x = 0.0f;
	float y = 0.0f;

	Vector2D() = default;
	Vector2D(float x, float y) : x(x), y(y) {}
	Vector2D(POINT point)
		: x(static_cast<float>(point.x)), y(static_cast<float>(point.y)) {}
	Vector2D(SIZE size)
		: x(static_cast<float>(size.cx)), y(static_cast<float>(size.cy)) {}

	operator POINT()
	{
		return { static_cast<int>(x), static_cast<int>(y) };
	}
	operator SIZE()
	{
		return { static_cast<int>(x), static_cast<int>(y) };
	}

	Vector2D operator+(const Vector2D& rValue) const
	{
		return Vector2D(this->x + rValue.x, this->y + rValue.y);
	}
	void operator+=(const Vector2D& rValue)
	{
		x += rValue.x;
		y += rValue.y;
	}

	Vector2D operator-(const Vector2D& rValue) const
	{
		return Vector2D(this->x - rValue.x, this->y - rValue.y);
	}
	void operator-=(const Vector2D& rValue)
	{
		x -= rValue.x;
		y -= rValue.y;
	}
	
	Vector2D operator*(const float& scalar)
	{
		return Vector2D(x * scalar, y * scalar);
	}
	void operator*=(const float& scalar)
	{
		x *= scalar;
		y *= scalar;
	}

	Vector2D operator/(const float& scalar)
	{
		return Vector2D(x / scalar, y / scalar);
	}
	void operator/=(const float& scalar)
	{
		x /= -scalar;
		y /= scalar;
	}

	bool operator==(const Vector2D other)
	{
		return (x == other.x && y == other.y);
	}
	bool operator!=(const Vector2D other)
	{
		return (x != other.x || y != other.y);
	}

	float Length() const
	{
		return sqrtf(powf(x, 2) + powf(y, 2));
	}

	Vector2D GetNormalized() const
	{
		float length = Length();
		return Vector2D(x / length, y / length);
	}
	void Normalized()
	{
		float length = Length();
		x /= length;
		y /= length;
	}
};
