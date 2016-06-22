//Library Includes
#include <windows.h>
#include <windowsx.h>

//Local Includes
#include "resource.h"
#include "Game.h"
#include "Clock.h"
#include "utils.h"
#include "level.h"
#include "player.h"

// Constants
#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"
const int kiWidth = 762;
const int kiHeight = 762;

// Global variables
HINSTANCE g_hInstance;
static int g_hCurrentPlayerShipSpeed;
static int g_hCurrentPlayerBulletSpeed;
static int g_hCurrentAlienShipSpeed;
static int g_hCurrentAlienBulletSpeed;

BOOL CALLBACK 
DebugWindowProc(HWND _hDlg, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam) {

	switch (_uiMsg) {

		case WM_INITDIALOG:
		{

			switch (g_hCurrentPlayerShipSpeed) {

			case -1:
				Button_SetCheck(GetDlgItem(_hDlg, IDC_PLAYER_SHIP_SLOW), BST_CHECKED);
				break;
			case 0:
				Button_SetCheck(GetDlgItem(_hDlg, IDC_PLAYER_SHIP_DEFAULT), BST_CHECKED);
				break;
			default:
				Button_SetCheck(GetDlgItem(_hDlg, IDC_PLAYER_SHIP_FAST), BST_CHECKED);
				break;

			}

			switch (g_hCurrentPlayerBulletSpeed) {

			case -1:
				Button_SetCheck(GetDlgItem(_hDlg, IDC_PLAYER_BULLET_SLOW), BST_CHECKED);
				break;
			case 0:
				Button_SetCheck(GetDlgItem(_hDlg, IDC_PLAYER_BULLET_DEFAULT), BST_CHECKED);
				break;
			default:
				Button_SetCheck(GetDlgItem(_hDlg, IDC_PLAYER_BULLET_FAST), BST_CHECKED);
				break;

			}
			
			switch (g_hCurrentAlienShipSpeed) {

			case -1:
				Button_SetCheck(GetDlgItem(_hDlg, IDC_ALIEN_SHIP_SLOW), BST_CHECKED);
				break;
			case 0:
				Button_SetCheck(GetDlgItem(_hDlg, IDC_ALIEN_SHIP_DEFAULT), BST_CHECKED);
				break;
			default:
				Button_SetCheck(GetDlgItem(_hDlg, IDC_ALIEN_SHIP_FAST), BST_CHECKED);
				break;

			}

			switch (g_hCurrentAlienBulletSpeed) {

			case -1:
				Button_SetCheck(GetDlgItem(_hDlg, IDC_ALIEN_BULLET_SLOW), BST_CHECKED);
				break;
			case 0:
				Button_SetCheck(GetDlgItem(_hDlg, IDC_ALIEN_BULLET_DEFAULT), BST_CHECKED);
				break;
			default:
				Button_SetCheck(GetDlgItem(_hDlg, IDC_ALIEN_BULLET_FAST), BST_CHECKED);
				break;

			}

			return TRUE;
			break;

		}

		case WM_COMMAND:
		{

			switch (LOWORD(_wParam)) {

				// Player ship speed
				case IDC_PLAYER_SHIP_SLOW:
					g_hCurrentPlayerShipSpeed = -1;
					CGame::GetInstance().GetLevel()->GetPlayer()->SetShipSpeed(350);
					break;
				case IDC_PLAYER_SHIP_DEFAULT:
					g_hCurrentPlayerShipSpeed = 0;
					CGame::GetInstance().GetLevel()->GetPlayer()->SetShipSpeed(550);
					break;
				case IDC_PLAYER_SHIP_FAST:
					g_hCurrentPlayerShipSpeed = 1;
					CGame::GetInstance().GetLevel()->GetPlayer()->SetShipSpeed(950);
					break;

				// Player Bullet Speed
				case IDC_PLAYER_BULLET_SLOW:
						g_hCurrentPlayerBulletSpeed = -1;
						CGame::GetInstance().GetLevel()->GetPlayer()->SetBulletSpeed(550);
					break;
					case IDC_PLAYER_BULLET_DEFAULT:
						g_hCurrentPlayerBulletSpeed = 0;
						CGame::GetInstance().GetLevel()->GetPlayer()->SetBulletSpeed(750);
					break;
					case IDC_PLAYER_BULLET_FAST:
						g_hCurrentPlayerBulletSpeed = 1;
						CGame::GetInstance().GetLevel()->GetPlayer()->SetBulletSpeed(2500);
					break;

				// Alien ship speed
				case IDC_ALIEN_SHIP_SLOW:
					g_hCurrentAlienShipSpeed = -1;
					//CGame::GetInstance().GetLevel()->GetPlayer()->SetShipSpeed(250);
					break;
				case IDC_ALIEN_SHIP_DEFAULT:
					g_hCurrentAlienShipSpeed = 0;
					//CGame::GetInstance().GetLevel()->GetPlayer()->SetShipSpeed(250);
					break;
				case IDC_ALIEN_SHIP_FAST:
					g_hCurrentAlienShipSpeed = 1;
					//CGame::GetInstance().GetLevel()->GetPlayer()->SetShipSpeed(250);
					break;

					// Alien bullet speed
				case IDC_ALIEN_BULLET_SLOW:
					g_hCurrentAlienBulletSpeed = -1;
					
					break;
				case IDC_ALIEN_BULLET_DEFAULT:
					g_hCurrentAlienBulletSpeed = 0;

					break;
				case IDC_ALIEN_BULLET_FAST:
					g_hCurrentAlienBulletSpeed = 1;

					break;

				case IDOK:

					//ShowWindow(_hDlg, SW_HIDE);
					EndDialog(_hDlg, 0);

					break;

			}

			return TRUE;
			break;

		}

		case WM_CLOSE:
		{

			EndDialog(_hDlg, 0);
			return TRUE;
			break;

		}

	}

	return FALSE;

}

LRESULT CALLBACK
WindowProc(HWND _hWnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam) {

	switch (_uiMsg) {

		case WM_CREATE:
		{

			ShowCursor(true);

		}
		break;

		case WM_KEYDOWN:
		{

			switch (WPARAM(_wParam)) {

				case VK_ESCAPE:
				DialogBox(g_hInstance, MAKEINTRESOURCE(DEBUG_WINDOW), NULL, DebugWindowProc);
				break;

			}
			
		}
		break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);

			return(0);
		}
		break;

		default:
			break;
	
	}

	return (DefWindowProc(_hWnd, _uiMsg, _wParam, _lParam));

}

HWND
CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, const wchar_t* _pcTitle) {

	WNDCLASSEX winclass;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(BLACK_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winclass)) {
		// Failed to register.
		return (0);
	}

	// Centering the window based on the screen's resolution
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);

	// Center it based on the screens resolution minus the window's dimensions
	int centerX = (screenX / 2) - (kiWidth / 2);
	int centerY = (screenY / 2) - (kiHeight / 2);

	HWND hwnd = CreateWindowEx(
		NULL,
		WINDOW_CLASS_NAME,
		_pcTitle,
		WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
		centerX, centerY,
		_iWidth, _iHeight,
		NULL,
		NULL,
		_hInstance,
		NULL
	);

	if (!hwnd) {
		// Failed to create.
		return (0);
	}

	return (hwnd);
}

int WINAPI
WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow) {
	MSG msg;
	RECT _rect;
	ZeroMemory(&msg, sizeof(MSG));

	HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Space Invaders v1.0.0");

	CGame& rGame = CGame::GetInstance();

	GetClientRect(hwnd, &_rect);

	//if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
	if (!rGame.Initialise(_hInstance, hwnd, _rect.right, _rect.bottom)) {
		// Failed
		return (0);
	}

	while (msg.message != WM_QUIT) {

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			rGame.ExecuteOneFrame();
		}

	}

	CGame::DestroyInstance();

	return (static_cast<int>(msg.wParam));
}
