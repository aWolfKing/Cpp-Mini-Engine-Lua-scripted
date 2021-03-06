// MiniEngine_lua.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MiniEngine_lua.h"
#include "mainwindow.h"
#include <iostream>
#include <fstream>


#define MAX_LOADSTRING 100

HWND window = nullptr;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

	std::ofstream debug_log_file;
	debug_log_file.open("debug.log");
	auto std_buf_was = std::cout.rdbuf();
	std::cout.rdbuf(debug_log_file.rdbuf());


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MINIENGINELUA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINIENGINELUA));

    MSG msg;

	
	mini_engine::main_window::sLua_manager.initialize();

	/*
    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
	*/

	bool quit = false;

	std::string Lua_update_funtion_name = "update30";
	std::string Lua_draw_function_name = "draw";

	//https://gamedev.stackexchange.com/questions/59857/game-loop-on-windows
	for (;;) {

		if (quit) {
			break;
		}

		DWORD start_time_tick = GetTickCount();
		DWORD end_time_tick = start_time_tick + (1000 / window_framerate);


		while (start_time_tick < end_time_tick) {
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) {
					quit = true;
					break;
				}
				else {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else {
				break;
			}
		}


		int inp_x{ 0 }, inp_y{ 0 }, inp_space{ 0 };

		inp_x = ((GetKeyState(VK_RIGHT) & 0x8000) != 0) - ((GetKeyState(VK_LEFT) & 0x8000) != 0);
		inp_y = (((GetKeyState(VK_UP) & 0x8000) != 0) - ((GetKeyState(VK_DOWN) & 0x8000) != 0)) * -1;
		inp_space = (GetKeyState(VK_SPACE) & 0x8000) != 0;

		mini_engine::main_window::sLua_manager.update_input(inp_x, inp_y, inp_space);

		//Call loaded Lua script's update function.
		mini_engine::main_window::sLua_manager.call_lua_defined_function(Lua_update_funtion_name);
		//Call loaded Lua script's draw function.
		mini_engine::main_window::sLua_manager.call_lua_defined_function(Lua_draw_function_name);

		if (window) {
			InvalidateRect(window, NULL, false);
			//UpdateWindow(window);
		}

	}


	mini_engine::main_window::sLua_manager.cleanup();


	std::cout.rdbuf(std_buf_was);

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINIENGINELUA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MINIENGINELUA);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      (GetSystemMetrics(SM_CXSCREEN)*0.5) - (window_size_x*0.5), (GetSystemMetrics(SM_CYSCREEN)*0.5) - (window_size_y*0.5), window_size_x, window_size_y, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   window = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_FILE_RELOAD:
				mini_engine::main_window::reload_file();
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
				window = nullptr;
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
			/*
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
			*/
			//PAINTSTRUCT ps;
			//HDC hdc = BeginPaint(hWnd, &ps);

			mini_engine::main_window::paint(hWnd);

			//EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		window = nullptr;
		mini_engine::main_window::on_destroy();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
