#include "resource.h"
#include <Windows.h>
#include <ScrnSave.h>

#include <cstdlib>
#include <time.h>

// Logo size
#define LOGO_WIDTH 420
#define LOGO_HEIGHT 202

#define szAppName "DVD Screensaver"
#define szPreview "DVD Screensaver 1.0"

LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static UINT uTimer = 0;

	static HBITMAP hLogoBitmap = NULL;

	static BOOL movingRight = TRUE, movingBottom = TRUE;
	static int posX, posY;
	static RECT rc;

	switch (message)
	{
	case WM_CREATE:
	{
		hLogoBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_LOGO));

		uTimer = SetTimer(hWnd, 1, 1, NULL);
		GetWindowRect(hWnd, &rc);

		srand((unsigned int)(NULL));

		// random initial logo position
		posX = rand() % (GetSystemMetrics(SM_CXSCREEN) - LOGO_WIDTH );
		posY = rand() % (GetSystemMetrics(SM_CYSCREEN) - LOGO_HEIGHT);

	}
	break;
	case WM_DESTROY:
	{

		if (uTimer)
			KillTimer(hWnd, uTimer);

		if (hLogoBitmap)
			DeleteObject(hLogoBitmap);

		PostQuitMessage(0);
		break;
	}
	case WM_TIMER:
	{
		if (!fChildPreview)
		{
			// process logo movement when not in preview mode
			int resX = GetSystemMetrics(SM_CXSCREEN);
			int resY = GetSystemMetrics(SM_CYSCREEN);

			posX += movingRight ? 1 : -1;
			posY += movingBottom ? 1 : -1;

			if (movingRight && posX > resX - LOGO_WIDTH)
				movingRight = FALSE;
			else if (!movingRight && posX < 1)
				movingRight = TRUE;

			if (movingBottom && posY > resY - LOGO_HEIGHT)
				movingBottom = FALSE;
			else if (!movingBottom && posY < 1)
				movingBottom = TRUE;

			rc.left = max(0, posX);
			rc.right = posX + LOGO_WIDTH;
			rc.top = max(0, posY);
			rc.bottom = posY + LOGO_HEIGHT;

			InvalidateRect(hWnd, &rc, FALSE);
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
			BITMAP bm;

			HDC hdcMem = CreateCompatibleDC(hDC);
			HGDIOBJ hbmOld = SelectObject(hdcMem, hLogoBitmap);

			GetObject(hLogoBitmap, sizeof(bm), &bm);

			BitBlt(hDC, posX, posY, LOGO_WIDTH, LOGO_HEIGHT, hdcMem, 0, 0, SRCCOPY);

			SelectObject(hdcMem, hbmOld);
			DeleteDC(hdcMem);

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
