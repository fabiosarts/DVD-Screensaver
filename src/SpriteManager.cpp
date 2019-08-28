#include "SpriteManager.hpp"

SpriteManager::SpriteManager()
{
	monitorRects = new MonitorRects();

	for (unsigned int i = 0u; i < monitorRects->rcMonitors.size(); i++)
	{
		sprites.push_back(new Sprite(monitorRects->rcMonitors.at(i)));
	}
}

SpriteManager::~SpriteManager()
{
	while (!sprites.empty())
	{
		delete sprites.back();
		sprites.pop_back();
	}
}

void SpriteManager::Draw(const HDC& hDC)
{
	for (unsigned int i = 0u; i < monitorRects->rcMonitors.size(); i++)
	{
		sprites.at(i)->Draw(hDC);
	}
}

void SpriteManager::Process(const HWND& hWnd)
{
	for (unsigned int i = 0u; i < monitorRects->rcMonitors.size(); i++)
	{
		sprites.at(i)->Process(hWnd);
	}
}
