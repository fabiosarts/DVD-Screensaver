#include "Sprite.hpp"

#include "utils.hpp"

Sprite::Sprite(const RECT& area)
{
	this->movingRight = (rand() % 2) == 1;
	this->movingBottom = (rand() % 2) == 1;

	this->movingArea = area;
	this->hLogoBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_LOGO));

	this->position.x = utils::getRandomRange(movingArea.left, movingArea.right - LOGO_WIDTH);
	this->position.y = utils::getRandomRange(movingArea.top, movingArea.bottom - LOGO_HEIGHT);
}

Sprite::~Sprite()
{
	if (hLogoBitmap)
		DeleteObject(hLogoBitmap);
}

void Sprite::Draw(const HDC& hDC)
{
	BITMAP bm;

	HDC hdcMem = CreateCompatibleDC(hDC);
	HGDIOBJ hbmOld = SelectObject(hdcMem, hLogoBitmap);

	GetObject(hLogoBitmap, sizeof(bm), &bm);

	BitBlt(hDC, this->position.x, this->position.y, LOGO_WIDTH, LOGO_HEIGHT, hdcMem, 0, 0, SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
}

void Sprite::move(const int& x, const int& y)
{
	this->position.x = x;
	this->position.y = y;
}

void Sprite::Process(const HWND & hWnd)
{
	this->position.x += movingRight ? 1 : -1;
	this->position.y += movingBottom ? 1 : -1;

	if (movingRight && this->position.x > this->movingArea.right - LOGO_WIDTH)
		movingRight = FALSE;
	else if (!movingRight && this->position.x < this->movingArea.left)
		movingRight = TRUE;

	if (movingBottom && this->position.y > this->movingArea.bottom - LOGO_HEIGHT)
		movingBottom = FALSE;
	else if (!movingBottom && this->position.y < this->movingArea.top)
		movingBottom = TRUE;

	rc.left = max(0, this->position.x);
	rc.right = this->position.x + LOGO_WIDTH;
	rc.top = max(0, this->position.y);
	rc.bottom = this->position.y + LOGO_HEIGHT;

	InvalidateRect(hWnd, &rc, FALSE);
}
