#include "resource.h"
#include <Windows.h>
#include <ScrnSave.h>

#include <cstdlib>
#include <time.h>

#include "SpriteManager.hpp"

#define szAppName "DVD Screensaver"
#define szPreview "DVD Screensaver 1.1"

LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static UINT uTimer = 0;

	static SpriteManager* spritesManager;

	switch (message)
	{
	case WM_CREATE:
	{
		uTimer = SetTimer(hWnd, 1, 15, NULL);

		srand((unsigned int)time(NULL));

		spritesManager = new SpriteManager();
	}
	break;
	case WM_DESTROY:
	{

		if (uTimer)
			KillTimer(hWnd, uTimer);

		delete spritesManager;
		spritesManager = NULL;

		PostQuitMessage(0);
		break;
	}
	case WM_TIMER:
	{
		if (!fChildPreview)
		{
			spritesManager->Process(hWnd);
		}
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);

		if (fChildPreview)
		{
			TextOut(hDC, 5, 5, szPreview, strlen(szPreview));
		}
		else
		{
			spritesManager->Draw(hDC);
		}
		EndPaint(hWnd, &ps);
	}
	break;
	default:
		return DefScreenSaverProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

BOOL WINAPI RegisterDialogClasses(HANDLE hInst)
{
	return TRUE;
}
