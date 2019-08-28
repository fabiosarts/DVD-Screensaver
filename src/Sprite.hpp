#ifndef Sprite_h__
#define Sprite_h__

#include <windows.h>

#include "resource.h"

#define LOGO_WIDTH 420
#define LOGO_HEIGHT 202

class Sprite
{
public:
	Sprite(const RECT& area);
	~Sprite();
	void Draw(const HDC& hDC);
	void move(const int& x, const int& y);
	void Process(const HWND& hWnd);
private:
	POINT position;
	RECT movingArea;
	HBITMAP hLogoBitmap;
	RECT rc;
	BOOL movingRight, movingBottom;
};
#endif // Sprite_h__

