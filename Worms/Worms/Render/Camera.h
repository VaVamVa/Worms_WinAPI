#pragma once

class ImageRect;
class GameObject;

class Camera : public Singleton<Camera>
{
private:
	const float FOLLOW_SPEED = 500.0f;

private:
	friend Singleton;
	Camera();
	~Camera();

public:
	void Update();

	void SetMap(ImageRect* landImage);
	void SetTarget(GameObject* target);
	const GameObject* GetTarget() { return target; }

	Rect* GetCamera() { return camera; }

private:
	void FreeMode();
	void FollowMode();
	bool FixPos();

private:
	Rect* camera = nullptr;
	float moveSpeed = FOLLOW_SPEED;
	Vector2D offset;
	Vector2D destPos;

	ImageRect* landImage = nullptr;
	GameObject* target = nullptr;
};