#include "framework.h"

ImageRect::ImageRect(std::wstring fileName, int frameX, int frameY, COLORREF transparentColor)
	:maxFrame({frameX, frameY})
{
	texture = Texture::Add(fileName, frameX, frameY, transparentColor);
	size = texture->GetFrameSize();
	camRect.SetSize(size.x, size.y);
}

ImageRect::ImageRect(Texture* texture)
{
	this->texture = texture;
	maxFrame = Vector2D(texture->GetFrame());
	size = texture->GetFrameSize();
	camRect.SetSize(size.x, size.y);
}

ImageRect::~ImageRect()
{
}

void ImageRect::Render(HDC hdc, POINT curFrame, bool isTransparent)
{
	texture->Render(hdc, this, curFrame, isTransparent);
}

void ImageRect::CamRender(HDC hdc, POINT curFrame, bool isTransparent)
{
	camRect.SetPos(pos - CAM->GetCamera()->GetPos());
	texture->Render(hdc, &camRect, curFrame, isTransparent);
}

void ImageRect::CamRender(HDC hdc, float speed, POINT curFrame, bool isTransparent)
{
	camRect.SetPos(pos - CAM->GetCamera()->GetPos() * speed);
	texture->Render(hdc, &camRect, curFrame, isTransparent);
}

void ImageRect::SetImageToObjectSize(GameObject* object)
{
	texture->SetImageToObjectSize(object);
}
