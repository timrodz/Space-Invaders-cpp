// Library Includes

// Local Includes
#include "Game.h"
#include "player.h"
#include "alien.h"
#include "bullet.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"

// This Include
#include "Level.h"

// Constants
#define ALIEN_COLUMNS 10
#define ALIEN_ROWS 5

// Static Variables
int CLevel::m_iPlayerLives = 3;

// Static Function Prototypes

// Implementation

#define CHEAT_BOUNCE_ON_BACK_WALL

CLevel::CLevel()
	: m_iAliensRemaining(0)
	, m_pPlayer(0)
	, m_pBullet(0)
	, m_iWidth(0)
	, m_iHeight(0)
	, m_fpsCounter(0) {}

CLevel::~CLevel() {

	while (m_vecAliens.size() > 0) {
		CAlien* pBrick = m_vecAliens[m_vecAliens.size() - 1];

		m_vecAliens.pop_back();

		delete pBrick;
	}

	delete m_pPlayer;
	m_pPlayer = 0;

	delete m_pBullet;
	m_pBullet = 0;

	delete m_fpsCounter;
	m_fpsCounter = 0;

}

bool CLevel::Initialise(int _iWidth, int _iHeight) {

	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	m_pPlayer = new CPlayer();
	VALIDATE(m_pPlayer->Initialise());

	// Set the paddle's position to be centered on the x, 
	// and a little bit up from the bottom of the window.
	m_pPlayer->SetX(_iWidth / 2.0f);
	m_pPlayer->SetY(_iHeight - (1.5f * m_pPlayer->GetHeight() / 2));

	const int kiNumAliens = 55;
	const int kiStartX = _iWidth / 6 - 35 + ALIEN_COLUMNS;
	const int kiGap = 5;

	int iCurrentX = kiStartX;
	int iCurrentY;

	for (int i = 0; i < ALIEN_COLUMNS; i++) {

		m_aliens[i].clear();
		iCurrentY = 40;

		for (int j = 0; j < ALIEN_ROWS; j++) {

			CAlien* pAlien = new CAlien();
			VALIDATE(pAlien->Initialise());

			pAlien->SetX(static_cast<float>(iCurrentX));
			pAlien->SetY(static_cast<float>(iCurrentY));

			iCurrentY += 50;

			m_aliens[i].push_back(pAlien);

		}

		iCurrentX += static_cast<int>(12 * kiGap);

		if (iCurrentX > (_iWidth / 2 + _iWidth / 4 + _iWidth / 6)) {

			iCurrentX = kiStartX;
			iCurrentY += 50;

		}

	}

	SetAliensRemaining(ALIEN_COLUMNS * ALIEN_ROWS);
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

	return (true);
}

void CLevel::Draw() {

	//m_pBackground->Draw();

	m_pPlayer->Draw();

	for (unsigned int i = 0; i < m_vecPlayerBullets.size(); ++i) {
		m_vecPlayerBullets[i]->Draw();
	}

	for (int i = 0; i < ALIEN_COLUMNS; i++) {

		for (int j = 0; j < ALIEN_ROWS; j++) {

			m_aliens[i].at(j)->Draw();

		}

	}

	DrawScore();
	DrawFPS();

}

void CLevel::Process(float _fDeltaTick) {

	m_pPlayer->Process(_fDeltaTick);

	ProcessBulletEdgeCollision();
	ProcessBulletAlienCollision();
	//ProcessBulletPlayerCollision();

	ProcessCheckForWin();

	for (unsigned int i = 0; i < m_vecPlayerBullets.size(); ++i) {
		m_vecPlayerBullets[i]->Process(_fDeltaTick);
	}

	for (int i = 0; i < ALIEN_COLUMNS; i++) {

		for (int j = 0; j < ALIEN_ROWS; j++) {

			m_aliens[i].at(j)->Process(_fDeltaTick);

		}

		if (m_aliens[i].back() != nullptr)
			m_aliens[i].back()->SetCanShoot();

	}

	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);

}

void CLevel::ResetLevel() {

	Initialise(m_iWidth, m_iHeight);

	if (m_iPlayerLives == 0) {

		CGame::GetInstance().GameOverLost();

	}

}

void CLevel::SetAlienShipSpeed(float _fSpeed) {

	for (int i = 0; i < ALIEN_COLUMNS; i++) {

		for (int j = 0; j < ALIEN_ROWS; j++) {

			m_aliens[i].at(j)->SetShipSpeed(_fSpeed);

		}

	}

}

void CLevel::SetAlienBulletSpeed(float _fSpeed) {

	for (int i = 0; i < ALIEN_COLUMNS; i++) {

		for (int j = 0; j < ALIEN_ROWS; j++) {

			m_aliens[i].at(j)->SetBulletSpeed(_fSpeed);

		}

	}

}

void CLevel::ProcessBulletAlienCollision() {

	for (int i = 0; i < ALIEN_COLUMNS; i++) {

		for (int j = 0; j < ALIEN_ROWS; j++) {

			if (!m_aliens[i].at(j)->IsHit()) {

				if (m_pPlayer->GetBullet() != nullptr) {

					float fBulletR = m_pPlayer->GetBullet()->GetRadius();

					float fBulletX = m_pPlayer->GetBullet()->GetX();
					float fBulletY = m_pPlayer->GetBullet()->GetY();

					float fAlienX = m_aliens[i].at(j)->GetX();
					float fAlienY = m_aliens[i].at(j)->GetY();

					float fAlienH = m_aliens[i].at(j)->GetHeight();
					float fAlienW = m_aliens[i].at(j)->GetWidth();

					if ((fBulletX + fBulletR > fAlienX - fAlienW / 2) &&
						(fBulletX - fBulletR < fAlienX + fAlienW / 2) &&
						(fBulletY + fBulletR > fAlienY - fAlienH / 2) &&
						(fBulletY - fBulletR < fAlienY + fAlienH / 2)) 
					{

						m_pPlayer->DestroyBullet();
						m_aliens[i].at(j)->SetHit(true);
						SetAliensRemaining(GetAliensRemaining() - 1);

					}

				}

			}

		}

	}

}

void CLevel::ProcessBulletPlayerCollision() {

	if (!m_pPlayer->IsHit()) {

		for (int i = 0; i < ALIEN_COLUMNS; i++) {

			for (int j = 0; j < ALIEN_ROWS; j++) {

				if (!m_aliens[i].at(j)->IsHit()) {

					if (m_aliens[i].at(j)->GetBullet() != nullptr) {

						float fBulletR =  m_aliens[i].at(j)->GetBullet()->GetRadius();

						float fBulletX =  m_aliens[i].at(j)->GetBullet()->GetX();
						float fBulletY =  m_aliens[i].at(j)->GetBullet()->GetY();

						float fPlayerX = m_pPlayer->GetX();
						float fPlayerY = m_pPlayer->GetY();

						float fPlayerH = m_pPlayer->GetHeight();
						float fPlayerW = m_pPlayer->GetWidth();

						if ((fBulletX + fBulletR > fPlayerX - fPlayerW / 2) &&
							(fBulletX - fBulletR < fPlayerX + fPlayerW / 2) &&
							(fBulletY + fBulletR > fPlayerY - fPlayerH / 2) &&
							(fBulletY - fBulletR < fPlayerY + fPlayerH / 2)) 
						{

							m_aliens[i].at(j)->DestroyBullet();
							m_pPlayer->SetHit(true);

						}

					}

				}

			}

		}

	}

}

void CLevel::ProcessBulletEdgeCollision() {

	if (m_pPlayer->GetBullet() != nullptr) {

		if (m_pPlayer->GetBullet()->GetY() < -m_pPlayer->GetBullet()->GetHeight()) {

			m_pPlayer->DestroyBullet();

		}

	}

}

void CLevel::ProcessCheckForWin() {

	if (m_pPlayer->IsHit()) {

		m_iPlayerLives--;

		// Reset the level
		CGame::GetInstance().GetLevel()->ResetLevel();

	}

	for (int i = 0; i < ALIEN_COLUMNS; i++) {

		for (int j = 0; j < ALIEN_ROWS; j++) {

			if (!m_aliens[i].at(j)->IsHit()) {

				return;

			}

		}

	}

	CGame::GetInstance().GameOverWon();

}

void CLevel::DrawScore() {

	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	const int kiX = 0;
	const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(255, 255, 255));
	TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
	SetTextColor(hdc, RGB(0, 0, 0));

}

void CLevel::UpdateScoreText() {

	m_strScore = "SCORE: ";
	m_strScore += ToString(GetAliensRemaining());

}


void CLevel::DrawFPS() {

	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();
	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}

CPlayer* CLevel::GetPlayer() const {

	return (m_pPlayer);

}

int CLevel::GetAliensRemaining() const {

	return (m_iAliensRemaining);

}

void CLevel::SetAliensRemaining(int _i) {

	m_iAliensRemaining = _i;
	UpdateScoreText();

}