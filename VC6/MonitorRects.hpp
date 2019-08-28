#ifndef MonitorRects_h__
#define MonitorRects_h__

// thanks: https://stackoverflow.com/questions/18112616/how-do-i-get-the-dimensions-rect-of-all-the-screens-in-win32-api

#include <Windows.h>
#include <vector>

struct MonitorRects
{
	// Adapted MonitorRects for Visual C++ 6.0 that only return the main monitor rect
	std::vector<RECT>   rcMonitors;
	RECT                rcCombined;

	MonitorRects()
	{
		RECT monitorRect = {
			0,
			0,
			GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CYSCREEN)
		};

		rcMonitors.push_back(monitorRect);
		rcCombined = monitorRect;
	}
};
#endif // MonitorRects_h__