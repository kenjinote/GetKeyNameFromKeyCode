#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib,"imm32.lib")

#include <windows.h>

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hStatic;
	switch (msg)
	{
	case WM_CREATE:
		hStatic = CreateWindow(TEXT("STATIC"), 0, WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		ImmAssociateContext(hWnd, 0);
		break;
	case WM_SIZE:
		MoveWindow(hStatic, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		break;
	case WM_KEYDOWN:
		{
			TCHAR szText[1024];
			if (GetKeyNameText((LONG)lParam, szText, _countof(szText)))
			{
				wsprintf(szText + lstrlen(szText), TEXT("(wParam=0x%X,lParam=0x%X)"), wParam, lParam);
			}
			else
			{
				wsprintf(szText, TEXT("Unknown wParam = 0x%X, lParam = 0x%X"), wParam, lParam);
			}
			SetWindowText(hStatic, szText);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("キーボードから入力されてキーの名前を表示"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
