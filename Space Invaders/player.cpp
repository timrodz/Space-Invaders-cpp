// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "player.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPlayer::CPlayer() :
	m_fShootTimer(0.0f),
	m_bCanShoot(false),
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
		CEntity::Draw();
	}

}

void
CPlayer::Process(float _fDeltaTick) {

	if (!m_bHit) {

		float fHalfPaddleW = m_pSprite->GetWidth() / 2.0f;

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {

			//CEntity::Initialise(IDB_SHIP_PLAYER_RIGHT_SPRITE, IDB_SHIP_PLAYER_RIGHT_MASK);
			m_fX += 400.0f * _fDeltaTick;

		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {

			//CEntity::Initialise(IDB_SHIP_PLAYER_LEFT_SPRITE, IDB_SHIP_PLAYER_LEFT_MASK);
			m_fX -= 400.0f * _fDeltaTick;

		}
		else {

			//if (CheckSprite(IDB_SHIP_PLAYER_SPRITE, IDB_SHIP_PLAYER_MASK))
			//CEntity::Initialise(IDB_SHIP_PLAYER_SPRITE, IDB_SHIP_PLAYER_MASK);

		}

		if (m_fX - fHalfPaddleW <= 0) {

			m_fX = fHalfPaddleW;

		}
		else if (m_fX + fHalfPaddleW >= 747) {

			m_fX = 747 - fHalfPaddleW;

		}

		CEntity::Process(_fDeltaTick);

	}

}

void
CPlayer::SetHit(bool _b) {
	m_bHit = _b;
}

bool
CPlayer::IsHit() const {
	return (m_bHit);
}
