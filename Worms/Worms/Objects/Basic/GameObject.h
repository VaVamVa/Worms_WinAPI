#pragma once

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void CamRender(HDC hdc);

	virtual bool IsCollision(GameObject* other);
	virtual bool IsCollision(Vector2D pos, Vector2D size);
	game_math::CardinalPoints DirectionalCollision(GameObject* other);

	const Vector2D GetPos() const { return pos; }
	const Vector2D GetSize() const { return size; }
	const float Left() const { return left; }
	const float Right() const { return right; }
	const float Top() const { return top; }
	const float Bottom() const { return bottom; }


	bool IsActive() { return active; }

	void SetActive(bool active) { this->active = active; }
	void SetPos(Vector2D pos) { this->pos = pos; }
	void SetPos(float x, float y) { this->pos = { x, y }; }
	void Translate(Vector2D direction) { pos += direction * DELTA; }

protected:
	bool IsPointCollision(GameObject* other);
	bool IsPointCollision(Vector2D pos);
	void SetOutLine();

private:
	bool CircleToRectCollision(GameObject* other);
	bool CircleToRectCollision(Vector2D pos, Vector2D size);

	bool RectToRectCollision(GameObject* other);
	bool RectToRectCollision(Vector2D pos, Vector2D size);

	bool CircleToCircleCollision(GameObject* other);
	bool CircleToCircleCollision(Vector2D pos, float range);

	bool RectToCircleCollision(Vector2D pos, float range);

	friend void Texture::SetImageToObjectSize(GameObject* object);

protected:
	Vector2D pos = {};
	Vector2D size = {};
	
	float left, top, right, bottom;

	bool active = false;

private:
	HPEN hitboxPen;
};