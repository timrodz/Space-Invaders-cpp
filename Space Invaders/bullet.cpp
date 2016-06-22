// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Includes
#include "bullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBullet::CBullet()
	: m_fVelocityY(0.0f)
{}

CBullet::~CBullet() 
{}

bool
CBullet::Initialise(short _iType, float _fPosX, float _fPosY, float _fVelocityY) {

	m_iType = _iType;

	// Player Bullet
	if (m_iType == 0) {

		VALIDATE(CEntity::Initialise(IDB_BULLET_PLAYER_SPRITE, IDB_BULLET_PLAYER_MASK));

	}
	// Enemy Bullet
	else {

		VALIDATE(CEntity::Initialise(IDB_BULLET_ENEMY_SPRITE, IDB_BULLET_ENEMY_MASK));

	}

	m_fX = _fPosX;
	m_fY = _fPosY;

	m_fVelocityY = _fVelocityY;

	return (true);
}

void
CBullet::Draw() {

	CEntity::Draw();

}

void
CBullet::Process(float _fDeltaTick) {

	if (m_iType == 0) {

		m_fY -= m_fVelocityY * _fDeltaTick;

	}
	else {
		
		m_fY += m_fVelocityY * _fDeltaTick;

	}

	CEntity::Process(_fDeltaTick);

}

float
CBullet::GetVelocityY() const {

	return (m_fVelocityY);

}

void
CBullet::SetVelocityY(float _fY) {

	m_fVelocityY = _fY;

}

float
CBullet::GetRadius() const {

	return (GetWidth() / 2.0f);

}
