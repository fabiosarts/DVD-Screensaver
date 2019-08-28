#ifndef MonitorRects_h__
#define MonitorRects_h__

// thanks: https://stackoverflow.com/questions/18112616/how-do-i-get-the-dimensions-rect-of-all-the-screens-in-win32-api

#include <Windows.h>
#include <vector>

struct MonitorRects
{
	std::vector<RECT>   rcMonitors;
	RECT                rcCombined;

	static BOOL CALLBACK MonitorEnum(HMONITOR hMon, HDC hdc, LPRECT lprcMonitor, LPARAM pData)
	{
		MonitorRects* pThis = reinterpret_cast<MonitorRects*>(pData);
		pThis->rcMonitors.push_back(*lprcMonitor);
		UnionRect(&pThis->rcCombined, &pThis->rcCombined, lprcMonitor);
		return TRUE;
	}

	MonitorRects()
	{
		SetRectEmpty(&rcCombined);
		EnumDisplayMonitors(0, 0, MonitorEnum, (LPARAM)this);
	}
};
#endif // MonitorRects_h__