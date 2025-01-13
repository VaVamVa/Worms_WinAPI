#include "framework.h"

Camera::Camera()
{
	camera = new Rect({ CLIENT_WIDTH, CLIENT_HEIGHT });
	offset = camera->GetSize() * 0.5f;
}

Camera::~Camera()
{
	delete camera;
}

void Camera::Update()
{
	if (V_KEY->Press(VK_RBUTTON))
	{
		FreeMode();
		return;
	}
	FollowMode();

	FixPos();
}

void Camera::SetMap(ImageRect* landImage)
{
	this->landImage = landImage;
	camera->SetPos(landImage->Left(), landImage->Bottom());
	FixPos();
}

void Camera::SetTarget(GameObject* target)
{
	this->target = target;
}


void Camera::FreeMode()
{
	if (V_KEY->Press('A'))
		camera->Translate(Vector2D(-moveSpeed, 0) * DELTA);
	if (V_KEY->Press('D'))
		camera->Translate(Vector2D(+moveSpeed, 0) * DELTA);
	if (V_KEY->Press('W'))
		camera->Translate(Vector2D(0, -moveSpeed) * DELTA);
	if (V_KEY->Press('S'))
		camera->Translate(Vector2D(0, +moveSpeed) * DELTA);
	FixPos();
}

void Camera::FollowMode()
{
	if (target == nullptr) return;

	camera->SetPos(target->GetPos() - offset);
	FixPos();
}

bool Camera::FixPos()
{
	if (landImage == nullptr) return false;

	bool isFix = false;

	Vector2D camPos = camera->GetPos();
	if (camPos.x < landImage->Left())
		camPos.x = landImage->Left();
	if (camPos.x > landImage->Right() - camera->GetSize().x)
		camPos.x = landImage->Right() - camera->GetSize().x;

	if (camPos.y < landImage->Top())
		camPos.y = landImage->Top();
	if (camPos.y > landImage->Bottom() - camera->GetSize().y)
		camPos.y = landImage->Bottom() - camera->GetSize().y;

	if (camPos != camera->GetPos())
		isFix = true;

	camera->SetPos(camPos);
	return isFix;
}