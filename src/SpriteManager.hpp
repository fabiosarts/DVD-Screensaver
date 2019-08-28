#ifndef SpriteManager_h__
#define SpriteManager_h__

#include <Windows.h>
#include <vector>

#include "Sprite.hpp"
#include "MonitorRects.hpp"

class SpriteManager
{
public:
	SpriteManager();
	~SpriteManager();
	void Draw(const HDC& hDC);
	void Process(const HWND& hWnd);
private:
	std::vector<Sprite*> sprites;
	MonitorRects* monitorRects;
};
#endif // SpriteManager_h__

