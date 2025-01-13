#pragma once

class Rect
{
public:
	Rect(Vector2D size = {}, Vector2D pos = {}) : size(size), pos(pos) {}
	~Rect() = default;

	float Left() { return pos.x - size.x * 0.5f; }
	float Right() { return pos.x + size.x * 0.5f; }
	float Top() { return pos.y - size.y * 0.5f; }
	float Bottom() { return pos.y + size.y * 0.5f; }

	Vector2D GetPos() { return pos; }
	Vector2D GetSize() { return size; }

	void SetSize(float width, float height) { size = { width, height }; }
	void SetSize(Vector2D size) { this->size = size; }

	void SetPos(float x, float y) { pos = { x, y }; }
	void SetPos(Vector2D pos) { this->pos = pos; }
	void Translate(Vector2D vector) { this->pos += vector; }
	void Translate(float dX, float dY) { pos += Vector2D(dX, dY); }

	const bool IsActive() const { return active; }

protected:
	Vector2D pos;
	Vector2D size;

	bool active = false;
};