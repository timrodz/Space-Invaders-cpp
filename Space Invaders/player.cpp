// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"
#include "bullet.h"

// This Include
#include "player.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPlayer::CPlayer() :
	m_fSpeed(550),
	m_fBulletSpeed(750),
	m_bCanShoot(true),
	m_bHit(false)
{}

CPlayer::~CPlayer() 
{}

bool
CPlayer::Initialise() {

	VALIDATE(CEntity::Initialise(IDB_SHIP_PLAYER_SPRITE, IDB_SHIP_PLAYER_MASK));

	return (true);

}

void
CPlayer::Draw() {
	
	if (!m_bHit) {
		
		if (m_pBullet != nullptr)
			m_pBullet->Draw();

		CEntity::Draw();

	}

}

void
CPlayer::Process(float _fDeltaTick) {

	if (!m_bHit) {

		if (m_bCanShoot && GetAsyncKeyState(VK_SPACE) & 0x8000) {

			m_pBullet = new CBullet();
			m_pBullet->Initialise(0, m_fX, m_fY - 28, GetBulletSpeed());

			m_bCanShoot = false;

		}

		float fHalfPaddleW = m_pSprite->GetWidth() / 2.0f;

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {

			m_pSprite->Deinitialise();
			m_pSprite->Initialise(IDB_SHIP_PLAYER_RIGHT_SPRITE, IDB_SHIP_PLAYER_RIGHT_MASK);
			m_fX += m_fSpeed * _fDeltaTick;

		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {

			m_pSprite->Deinitialise();
			m_pSprite->Initialise(IDB_SHIP_PLAYER_LEFT_SPRITE, IDB_SHIP_PLAYER_LEFT_MASK);
			m_fX -= m_fSpeed * _fDeltaTick;

		}
		else {

			m_pSprite->Deinitialise();
			m_pSprite->Initialise(IDB_SHIP_PLAYER_SPRITE, IDB_SHIP_PLAYER_MASK);

		}

		if (m_fX - fHalfPaddleW <= 0) {

			m_fX = fHalfPaddleW;

		}
		else if (m_fX + fHalfPaddleW >= 747) {

			m_fX = 747 - fHalfPaddleW;

		}

		if (m_pBullet != nullptr)
			m_pBullet->Process(_fDeltaTick);

		CEntity::Process(_fDeltaTick);

	}

}

void CPlayer::DestroyBullet() {

	m_bCanShoot = true;
	m_pBullet = nullptr;

}

CBullet* CPlayer::GetBullet() const {

	return (m_pBullet);

}

void 
CPlayer::SetShipSpeed(float _fSpeed) {

	m_fSpeed = _fSpeed;

}

float
CPlayer::GetBulletSpeed() const {

	return (m_fBulletSpeed);

}

void 
CPlayer::SetBulletSpeed(float _fSpeed) {

	m_fBulletSpeed = _fSpeed;

}

void
CPlayer::SetHit(bool _b) {

	m_bHit = _b;

}

bool
CPlayer::IsHit() const {

	return (m_bHit);

}