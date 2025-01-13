#include "framework.h"

GameObject::GameObject()
{
	hitboxPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 30));
}

GameObject::~GameObject()
{
	DeleteObject(hitboxPen);
}

void GameObject::Update()
{
    if (!active) return;
    SetOutLine();
}

void GameObject::Render(HDC hdc)
{
	SelectObject(hdc, hitboxPen);

	if (size.y == 0.0f)
	{
		Ellipse(hdc, static_cast<int>(left), static_cast<int>(top), static_cast<int>(right), static_cast<int>(bottom));
	}
	else
	{
		//Rectangle(hdc, static_cast<int>(left), static_cast<int>(top), static_cast<int>(right), static_cast<int>(bottom));
		int left = static_cast<int>(this->left), right = static_cast<int>(this->right),
			top = static_cast<int>(this->top), bottom = static_cast<int>(this->bottom);
		MoveToEx(hdc, left, top, nullptr);
		LineTo(hdc, right, top);

		MoveToEx(hdc, right, top, nullptr);
		LineTo(hdc, right, bottom);

		MoveToEx(hdc, right, bottom, nullptr);
		LineTo(hdc, left, bottom);

		MoveToEx(hdc, left, bottom, nullptr);
		LineTo(hdc, left, top);
	}
}

void GameObject::CamRender(HDC hdc)
{
	SelectObject(hdc, hitboxPen);
	left -= CAM->GetCamera()->GetPos().x;
	right -= CAM->GetCamera()->GetPos().x;
	top -= CAM->GetCamera()->GetPos().y;
	bottom -= CAM->GetCamera()->GetPos().y;

	if (!GameManager::DevMode())
		return;

	if (size.y == 0.0f)
	{
		Ellipse(hdc, static_cast<int>(left), static_cast<int>(top), static_cast<int>(right), static_cast<int>(bottom));
	}
	else
	{
		int left = static_cast<int>(this->left), right = static_cast<int>(this->right),
			top = static_cast<int>(this->top), bottom = static_cast<int>(this->bottom);
		//Rectangle(hdc, static_cast<int>(left), static_cast<int>(top), static_cast<int>(right), static_cast<int>(bottom));
		MoveToEx(hdc, left, top, nullptr);
		LineTo(hdc, right, top);

		MoveToEx(hdc, right, top, nullptr);
		LineTo(hdc, right, bottom);

		MoveToEx(hdc, right, bottom, nullptr);
		LineTo(hdc, left, bottom);

		MoveToEx(hdc, left, bottom, nullptr);
		LineTo(hdc, left, top);
	}
}

bool GameObject::IsCollision(GameObject* other)
{
	if (!active) return false;
	if (!other->active) return false;

	//https://codechacha.com/ko/cpp-min-max-in-array/
	float sizeArr[4] = { size.x * 0.5f, size.y * 0.5f, other->size.x * 0.5f, other->size.y * 0.5f };
	float maxSize = *std::max_element(std::begin(sizeArr), std::end(sizeArr));
	if ((pos - other->pos).Length() > maxSize * 2)
		return false;

	SetOutLine();
	other->SetOutLine();
	if (size.y == 0.0f)
	{
		if (other->GetSize().y == 0.0f)
			return CircleToCircleCollision(other);
		else
			return CircleToRectCollision(other);
	}
	else
	{
		if (other->GetSize().y == 0.0f)
			return other->CircleToRectCollision(this);
		else
			return RectToRectCollision(other);
	}
}

bool GameObject::IsCollision(Vector2D pos, Vector2D size)
{
	float sizeArr[4] = { this->size.x * 0.5f, this->size.y * 0.5f, size.x * 0.5f, size.y * 0.5f };
	float maxSize = *std::max_element(std::begin(sizeArr), std::end(sizeArr));
	if ((this->pos - pos).Length() > maxSize * 2)
		return false;
	SetOutLine();
	if (this->size.y == 0.0f)
	{
		if (size.y == 0.0f)
			return CircleToCircleCollision(pos, size.x);
		else
			return CircleToRectCollision(pos, size);
	}
	else
	{
		if (size.y == 0.0f)
			return RectToCircleCollision(pos, size.x);
		else
			return RectToRectCollision(pos, size);
	}
}

game_math::CardinalPoints GameObject::DirectionalCollision(GameObject* other)
{
	if (!active) return game_math::CardinalPoints::NONE;
	if (!other->active) return game_math::CardinalPoints::NONE;

	SetOutLine();
	other->SetOutLine();
	float maxLeft = max(other->left, left);
	float minRight = min(other->right, right);
	float maxTop = max(other->top, top);
	float minBottom = min(other->bottom, bottom);

	Vector2D overlappedSize = { minRight - maxLeft, minBottom - maxTop };
	if (overlappedSize.x > 0 && overlappedSize.y > 0)
	{
		if (overlappedSize.x > overlappedSize.y)
		{
			if (pos.y < other->pos.y)
			{
				other->pos += Vector2D(0, overlappedSize.y);
				return game_math::CardinalPoints::SOUTH;
			}
			else
			{
				other->pos += Vector2D(0, -overlappedSize.y);
				return game_math::CardinalPoints::NORTH;
			}
		}
		else
		{
			if (pos.x < other->pos.x)
			{
				other->pos += Vector2D(overlappedSize.x, 0);
				return game_math::CardinalPoints::EAST;
			}
			else
			{
				other->pos += Vector2D(-overlappedSize.x, 0);
				return game_math::CardinalPoints::WEST;
			}
		}
	}
	return game_math::CardinalPoints::NONE;
}

bool GameObject::IsPointCollision(GameObject* other)
{
	Vector2D edge;
	edge.x = pos.x < other->left ? other->left : other->right;
	edge.y = pos.y < other->top ? other->top : other->bottom;

	if ((edge - pos).Length() > size.x)
		return false;

	return true;
}

bool GameObject::IsPointCollision(Vector2D pos)
{
	if (pos.x < right && pos.x > left &&
		pos.y < bottom && pos.y > top)
		return true;

	return false;
}

void GameObject::SetOutLine()
{
	left = (pos.x) - (size.x * 0.5f);
	right = (pos.x) + (size.x * 0.5f);

	if (size.y == 0)
	{
		top = (pos.y) - (size.x * 0.5f);
		bottom = (pos.y) + (size.x * 0.5f);
	}
	else
	{
		top = (pos.y) - (size.y * 0.5f);
		bottom = (pos.y) + (size.y * 0.5f);
	}
}

bool GameObject::CircleToRectCollision(GameObject* other)
{
	if (pos.y > other->top && pos.y < other->bottom)
	{
		int maxLeft = static_cast<int>(max(other->left, left));
		int minRight = static_cast<int>(min(other->right, right));
		if (maxLeft < minRight)
		{
			if (pos.x < other->left)
				return true;
			else if (pos.x > other->right)
				return true;
		}
	}
	else if (pos.x > other->left && pos.x < other->right)
	{
		int maxTop = static_cast<int>(max(other->top, top));
		int minBottom = static_cast<int>(min(other->bottom, bottom));

		if (maxTop < minBottom)
		{
			if (pos.y < other->top)
				return true;
			else if (pos.y > other->bottom)
				return true;
		}
	}
	else
		return IsPointCollision(other);
	return false;
}

bool GameObject::CircleToRectCollision(Vector2D pos, Vector2D size)
{
	float left = pos.x - size.x;
	float top = pos.y - size.y;
	float right = pos.x + size.x;
	float bottom = pos.y + size.y;
	if (this->pos.y > top && this->pos.y < bottom)
	{
		int maxLeft = static_cast<int>(max(this->left, left));
		int minRight = static_cast<int>(min(this->right, right));
		if (maxLeft < minRight)
		{
			if (this->pos.x < left)
				return true;
			else if (this->pos.x > right)
				return true;
		}
	}
	else if (this->pos.x > left && this->pos.x < right)
	{
		int maxTop = static_cast<int>(max(this->top, top));
		int minBottom = static_cast<int>(min(this->bottom, bottom));

		if (maxTop < minBottom)
		{
			if (this->pos.y < top)
				return true;
			else if (this->pos.y > bottom)
				return true;
		}
	}
	return false;
}

bool GameObject::RectToRectCollision(GameObject* other)
{
	if (other->pos.x > left && other->pos.x < right)
	{
		int maxTop = static_cast<int>(max(other->top, top));
		int minBottom = static_cast<int>(min(other->bottom, bottom));

		if (maxTop <= minBottom)
			return true;
	}
	else if (other->pos.y > top && other->pos.y < bottom)
	{
		int maxLeft = static_cast<int>(max(other->left, left));
		int minRight = static_cast<int>(min(other->right, right));
		if (maxLeft <= minRight)
			return true;
	}
	return false;
}

bool GameObject::RectToRectCollision(Vector2D pos, Vector2D size)
{
	float left = pos.x - size.x;
	float top = pos.y - size.y;
	float right = pos.x + size.x;
	float bottom = pos.y + size.y;
	if (pos.x > this->left && pos.x < this->right)
	{
		int maxTop = static_cast<int>(max(this->top, top));
		int minBottom = static_cast<int>(min(this->bottom, bottom));

		if (maxTop <= minBottom)
			return true;
	}
	else if (pos.y > this->top && pos.y < this->bottom)
	{
		int maxLeft = static_cast<int>(max(this->left, left));
		int minRight = static_cast<int>(min(this->right, right));
		if (maxLeft <= minRight)
			return true;
	}
	return false;
}

bool GameObject::CircleToCircleCollision(GameObject* other)
{
	return other->size.x + size.x >= (other->pos - pos).Length();
}

bool GameObject::CircleToCircleCollision(Vector2D pos, float range)
{
	return this->size.x + range >= (this->pos - pos).Length();
}

bool GameObject::RectToCircleCollision(Vector2D pos, float range)
{
	float left = pos.x - range;
	float top = pos.y - range;
	float right = pos.x + range;
	float bottom = pos.y + range;
	if (this->pos.y > top && this->pos.y < bottom)
	{
		int maxLeft = static_cast<int>(max(this->left, left));
		int minRight = static_cast<int>(min(this->right, right));
		if (maxLeft < minRight)
		{
			return true;
		}
	}
	else if (this->pos.x > left && this->pos.x < right)
	{
		int maxTop = static_cast<int>(max(this->top, top));
		int minBottom = static_cast<int>(min(this->bottom, bottom));

		if (maxTop < minBottom)
		{
			return true;
		}
	}
	return false;
}
