// Library Includes

// Local Includes
#include "Clock.h"
#include "Level.h"
#include "BackBuffer.h"
#include "utils.h"
#include "background.h"
#include "cursor.h"

// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;

// Static Function Prototypes

// Implementation

CGame::CGame()
	: m_pLevel(0)
	, m_pClock(0)
	, m_hApplicationInstance(0)
	, m_hMainWindow(0)
	, m_pBackBuffer(0) {

	m_iState = MENU;

}

CGame::~CGame() {

	delete m_pLevel;
	m_pLevel = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pClock;
	m_pClock = 0;
	
	delete m_pCursor;
	m_pCursor = 0;

	delete m_pBackground;
	m_pBackground = 0;

}

bool
CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight) {

	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;

	m_pClock = new CClock();
	VALIDATE(m_pClock->Initialise());
	m_pClock->Process();

	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	m_pLevel = new CLevel();
	VALIDATE(m_pLevel->Initialise(_iWidth, _iHeight));

	m_pCursor = new CCursor(3);
	VALIDATE(m_pCursor->Initialise());
	m_pCursor->SetX(175);
	m_pCursor->SetY(485);

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from{ 0,0 }
	m_pBackground->SetX((float)_iWidth / 2);
	m_pBackground->SetY((float)_iHeight / 2);

	return (true);
}

void
CGame::Draw() {

	m_pBackBuffer->Clear();

	m_pBackground->Draw();

	switch (m_iState) {

		case MENU:

			m_pCursor->Draw();

			break;
		case PLAY:
			m_pLevel->Draw();
			break;
		case CREDITS:

			break;
		case GAMEOVER:

			break;

	}

	m_pBackBuffer->Present();
}

void
CGame::Process(float _fDeltaTick) {

	m_pBackground->Process(_fDeltaTick);

	switch (m_iState) {

		case MENU:

			m_pCursor->Process(_fDeltaTick);

			break;
		case PLAY:

			m_pLevel->Process(_fDeltaTick);

			break;
		case CREDITS:

			break;
		case GAMEOVER:

			break;

	}

}

void
CGame::ExecuteOneFrame() {

	float fDT = m_pClock->GetDeltaTick();

	Process(fDT);
	Draw();

	m_pClock->Process();

	Sleep(15);

}

CGame&
CGame::GetInstance() {

	if (s_pGame == 0) {
		s_pGame = new CGame();
	}

	return (*s_pGame);
}

void
CGame::GameOverWon() {

	MessageBox(m_hMainWindow, L"Winner!", L"Game Over", MB_OK);
	PostQuitMessage(0);

}

void
CGame::GameOverLost() {

	MessageBox(m_hMainWindow, L"Loser!", L"Game Over", MB_OK);
	PostQuitMessage(0);

}

void CGame::SetState(int _iState) {

	m_iState = _iState;

}

int
CGame::GetState() const {

	return (m_iState);

}


void
CGame::DestroyInstance() {

	delete s_pGame;
	s_pGame = 0;

}

CCursor * CGame::GetCursor() {
	
	return (m_pCursor);

}

CBackGround*
CGame::GetBackGround() {
	
	return (m_pBackground);

}

CBackBuffer*
CGame::GetBackBuffer() {

	return (m_pBackBuffer);

}

CLevel*
CGame::GetLevel() {

	return (m_pLevel);

}

HINSTANCE
CGame::GetAppInstance() {

	return (m_hApplicationInstance);

}

HWND
CGame::GetWindow() {

	return (m_hMainWindow);

}