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

// Static Variables

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

	delete m_pBackground;
	m_pBackground = 0;

}

bool
CLevel::Initialise(int _iWidth, int _iHeight) {

	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	const float fBulletVelX = 0.0f;
	const float fBulletVelY = 275.0f;

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);

	//m_pBullet = new CBullet();
	//VALIDATE(m_pBullet->Initialise(m_iWidth / 2.0f, m_iHeight / 2.0f, fBulletVelX, fBulletVelY));

	m_pPlayer = new CPlayer();
	VALIDATE(m_pPlayer->Initialise());

	// Set the paddle's position to be centered on the x, 
	// and a little bit up from the bottom of the window.
	m_pPlayer->SetX(_iWidth / 2.0f);
	m_pPlayer->SetY(_iHeight - (1.5f * m_pPlayer->GetHeight() / 2));

	const int kiNumAliens = 55;
	const int kiStartX = _iWidth / 6 - 15;
	const int kiGap = 5;

	int iCurrentX = kiStartX;
	int iCurrentY = 40;

	for (int i = 0; i < kiNumAliens; ++i) {

		CAlien* pBrick = new CAlien();
		VALIDATE(pBrick->Initialise());

		pBrick->SetX(static_cast<float>(iCurrentX));
		pBrick->SetY(static_cast<float>(iCurrentY));

		iCurrentX += static_cast<int>(pBrick->GetWidth()) + kiGap;

		if (iCurrentX > (_iWidth / 2 + _iWidth / 4 + _iWidth / 6)) {
			iCurrentX = kiStartX;
			iCurrentY += 50;
		}

		m_vecAliens.push_back(pBrick);

	}

	SetAliensRemaining(kiNumAliens);
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

	return (true);
}

void
CLevel::Draw() {

	m_pBackground->Draw();

	m_pPlayer->Draw();

	for (unsigned int i = 0; i < m_vecPlayerBullets.size(); ++i) {
		m_vecPlayerBullets[i]->Draw();
	}

	for (unsigned int i = 0; i < m_vecAliens.size(); ++i) {
		m_vecAliens[i]->Draw();
	}

	//m_pBullet->Draw();

	DrawScore();
	DrawFPS();

}

void
CLevel::Process(float _fDeltaTick) {

	m_pBackground->Process(_fDeltaTick);
	//m_pBullet->Process(_fDeltaTick);
	m_pPlayer->Process(_fDeltaTick);
	ProcessBulletAlienCollision();
	ProcessBallWallCollision();
	//ProcessPaddleWallCollison();
	//ProcessBallPaddleCollision();
	//ProcessBallBrickCollision();

	ProcessCheckForWin();
	//ProcessBallBounds();

	for (unsigned int i = 0; i < m_vecPlayerBullets.size(); ++i) {
		m_vecPlayerBullets[i]->Process(_fDeltaTick);
	}

	for (unsigned int i = 0; i < m_vecAliens.size(); ++i) {
		m_vecAliens[i]->Process(_fDeltaTick);
	}

	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);

}

CPlayer*
CLevel::GetPaddle() const {
	return (m_pPlayer);
}

void
CLevel::ProcessBallWallCollision() {

	for (unsigned int i = 0; i < m_vecPlayerBullets.size(); ++i) {

		float fBulletX = m_vecPlayerBullets[i]->GetX();
		float fBulletY = m_vecPlayerBullets[i]->GetY();
		float fBulletW = m_vecPlayerBullets[i]->GetWidth();
		float fBulletH = m_vecPlayerBullets[i]->GetHeight();

		float fHalfBulletW = fBulletW / 2;
		float fHalfBulletH = fBulletH / 2;

		/*if (fBulletX < fHalfBulletW) {
			m_vecPlayerBullets[i]->SetVelocityX(m_vecPlayerBullets[i]->GetVelocityX() * -1);
		}
		else if (fBulletX > m_iWidth - fHalfBulletW) {
			m_vecPlayerBullets[i]->SetVelocityX(m_vecPlayerBullets[i]->GetVelocityX() * -1);
		}*/

		if (fBulletY < fHalfBulletH) {
			m_vecPlayerBullets[i]->SetVelocityY(m_vecPlayerBullets[i]->GetVelocityY() * -1);
		}

	}

}




void
CLevel::ProcessBulletAlienCollision() {

	for (unsigned int i = 0; i < m_vecAliens.size(); ++i) {

		if (!m_vecAliens[i]->IsHit()) {

			for (unsigned int i = 0; i < m_vecPlayerBullets.size(); ++i) {

				float fBallR = m_vecPlayerBullets[i]->GetRadius();

				float fBallX = m_vecPlayerBullets[i]->GetX();
				float fBallY = m_vecPlayerBullets[i]->GetY();

				float fBrickX = m_vecAliens[i]->GetX();
				float fBrickY = m_vecAliens[i]->GetY();

				float fBrickH = m_vecAliens[i]->GetHeight();
				float fBrickW = m_vecAliens[i]->GetWidth();

				if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
					(fBallX - fBallR < fBrickX + fBrickW / 2) &&
					(fBallY + fBallR > fBrickY - fBrickH / 2) &&
					(fBallY - fBallR < fBrickY + fBrickH / 2)) {

					//Hit the front side of the brick...
					m_vecPlayerBullets[i]->SetY((fBrickY + fBrickH / 2.0f) + fBallR);
					m_vecPlayerBullets[i]->SetVelocityY(m_vecPlayerBullets[i]->GetVelocityY() * -1);
					m_vecAliens[i]->SetHit(true);

					SetAliensRemaining(GetAliensRemaining() - 1);

				}

			}

		}

	}

}

void
CLevel::ProcessBulletPlayerCollision() {

	for (unsigned int i = 0; i < m_vecEnemyBullets.size(); ++i) {

		float fBallR = m_vecEnemyBullets[i]->GetRadius();

		float fBallX = m_vecEnemyBullets[i]->GetX();
		float fBallY = m_vecEnemyBullets[i]->GetY();

		float fBrickX = m_pPlayer->GetX();
		float fBrickY = m_pPlayer->GetY();

		float fBrickH = m_pPlayer->GetHeight();
		float fBrickW = m_pPlayer->GetWidth();

		if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
			(fBallX - fBallR < fBrickX + fBrickW / 2) &&
			(fBallY + fBallR > fBrickY - fBrickH / 2) &&
			(fBallY - fBallR < fBrickY + fBrickH / 2)) {

			//Hit the front side of the brick...
			m_vecEnemyBullets[i]->SetY((fBrickY + fBrickH / 2.0f) + fBallR);
			m_vecEnemyBullets[i]->SetVelocityY(m_vecEnemyBullets[i]->GetVelocityY() * -1);
			//m_pPlayer->SetHit(true);

			SetAliensRemaining(GetAliensRemaining() - 1);

		}
	}

}

void
CLevel::ProcessCheckForWin() {

	for (unsigned int i = 0; i < m_vecAliens.size(); ++i) {
		if (!m_vecAliens[i]->IsHit()) {
			return;
		}
	}

	CGame::GetInstance().GameOverWon();
}

void
CLevel::ProcessBallBounds() {

	if (m_pBullet->GetX() < 0) {
		m_pBullet->SetX(0);
	}
	else if (m_pBullet->GetX() > m_iWidth) {
		m_pBullet->SetX(static_cast<float>(m_iWidth));
	}

	if (m_pBullet->GetY() < 0) {
		m_pBullet->SetY(0.0f);
	}
	else if (m_pBullet->GetY() > m_iHeight) {
		CGame::GetInstance().GameOverLost();
		//m_pBall->SetY(static_cast<float>(m_iHeight));
	}

}

int
CLevel::GetAliensRemaining() const {
	return (m_iAliensRemaining);
}

void
CLevel::SetAliensRemaining(int _i) {
	m_iAliensRemaining = _i;
	UpdateScoreText();
}

void
CLevel::DrawScore() {
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	const int kiX = 0;
	const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);

	TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}



void
CLevel::UpdateScoreText() {
	m_strScore = "Aliens Remaining: ";

	m_strScore += ToString(GetAliensRemaining());
}


void
CLevel::DrawFPS() {
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}
