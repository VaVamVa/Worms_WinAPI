#include "framework.h"

std::unordered_map<std::wstring, Texture*> Texture::textures;

Texture::Texture(std::wstring fileName, int frameX, int frameY, COLORREF transparentColor)
    :imageFrame({frameX, frameY}),
    transparentColor(transparentColor)
{
    HDC hdc = GetDC(hWnd);

    memDC = CreateCompatibleDC(hdc);

    try
    {
        hBitmap = (HBITMAP)LoadImage(hInst,
            fileName.c_str(),
            IMAGE_BITMAP,
            0, 0,
            LR_LOADFROMFILE
        );
        if (hBitmap == nullptr)
        {
            throw "Image Not Loaded";
        }
    }
    catch (std::string error_msg)
    {
        ::OutputDebugStringA(error_msg.c_str());
        ReleaseDC(hWnd, hdc);
        return;
    }

    SelectObject(memDC, hBitmap);

    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);
    this->imageSize = { bitmap.bmWidth, bitmap.bmHeight };
    this->cutSize = { imageSize.cx / imageFrame.x, imageSize.cy / imageFrame.y };

    ReleaseDC(hWnd, hdc);
}

Texture::~Texture()
{
    DeleteDC(memDC);
    DeleteObject(hBitmap);
}

Texture* Texture::Add(std::wstring fileName, int frameX, int frameY, COLORREF transparentColor)
{
    std::unordered_map<std::wstring, Texture*>::iterator iter = textures.find(fileName);

    if (iter != textures.end())
    {
        if (iter->second == nullptr)
            iter->second = new Texture(fileName, frameX, frameY, transparentColor);
        return iter->second;
    }

    Texture* texture = new Texture(fileName, frameX, frameY, transparentColor);
    textures.insert({ fileName, texture });
    return texture;
}

void Texture::Renewal(std::wstring file)
{
    std::unordered_map<std::wstring, Texture*>::iterator iter = textures.find(file);
    if (iter == textures.end())
        return;
    DeleteObject(iter->second->hBitmap);
    iter->second->hBitmap = 
        (HBITMAP)LoadImage(hInst,
        file.c_str(),
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE
    );
    SelectObject(iter->second->memDC, iter->second->hBitmap);
}

void Texture::Delete()
{
    for (std::pair<std::wstring, Texture*> texture : textures)
        delete texture.second;
    textures.clear();
}

void Texture::Render(HDC hdc, GameObject* object, POINT curFrame, bool isTransparent)
{
    if (!isTransparent)
    {
        BitBlt(hdc,
            static_cast<int>(object->GetPos().x - object->GetSize().x * 0.5f), static_cast<int>(object->GetPos().y - object->GetSize().y * 0.5f),
            static_cast<int>(object->GetSize().x), static_cast<int>(object->GetSize().y),
            memDC,
            cutSize.cx * curFrame.x,
            cutSize.cy * curFrame.y,
            SRCCOPY
        );
    }
    else
    {
        GdiTransparentBlt(hdc,
            static_cast<int>(object->GetPos().x - object->GetSize().x * 0.5f), static_cast<int>(object->GetPos().y - object->GetSize().y * 0.5f),
            static_cast<int>(object->GetSize().x), static_cast<int>(object->GetSize().y),
            memDC,
            cutSize.cx * curFrame.x,
            cutSize.cy * curFrame.y,
            cutSize.cx, cutSize.cy,
            transparentColor
        );
    }
}

void Texture::Render(HDC hdc, Rect* rect, POINT curFrame, bool isTransparent)
{
    if (!isTransparent)
    {
        BitBlt(hdc,
            (int)rect->Left(), (int)rect->Top(),
            (int)rect->GetSize().x, (int)rect->GetSize().y,
            memDC,
            cutSize.cx * curFrame.x,
            cutSize.cy * curFrame.y,
            SRCCOPY
        );
    }
    else
    {
        GdiTransparentBlt(hdc,
            (int)rect->Left(), (int)rect->Top(),
            (int)rect->GetSize().x, (int)rect->GetSize().y,
            memDC,
            cutSize.cx * curFrame.x,
            cutSize.cy * curFrame.y,
            cutSize.cx, cutSize.cy,
            transparentColor
        );
    }
}

void Texture::SetImageToObjectSize(GameObject* object)
{
    //object->size.x = static_cast<float>(cutSize.cx);
    //object->size.y = static_cast<float>(cutSize.cy);

    COLORREF color = transparentColor;
    RECT pixelRect = { cutSize.cx, cutSize.cy, };
    FOR(y, 0, cutSize.cy)
    {
        FOR(x, 0, cutSize.cx)
        {
            color = GetPixel(memDC, x, y);
            if (color != transparentColor)
            {
                pixelRect.left = min(pixelRect.left, x);
                pixelRect.right = max(pixelRect.right, x);
                pixelRect.top = min(pixelRect.top, y);
                pixelRect.bottom = max(pixelRect.bottom, y);
            }
        }
    }
    object->size = { static_cast<float>(pixelRect.right - pixelRect.left), static_cast<float>(pixelRect.bottom - pixelRect.top) };
}

const float Texture::GetEffectivePixelUnderPosY(const Vector2D& pos)
{
    int startY = pos.y < 0.0f ? 0 : static_cast<int>(pos.y);

    COLORREF color;
    FOR(y, startY, imageSize.cy)
    {
        color = GetPixel(memDC, (int)pos.x, y);

        if (color != transparentColor)
            return static_cast<float>(y);
    }
    return static_cast<float>(imageSize.cy);
}

const bool Texture::IsEffectivePixelPosY(const Vector2D& pos)
{
    COLORREF color = GetPixel(memDC, (int)pos.x, (int)pos.y);
    return color != transparentColor;
}
