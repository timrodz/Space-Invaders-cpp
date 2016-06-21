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
	: m_fVelocityX(0.0f)
	, m_fVelocityY(0.0f) {

}

CBullet::~CBullet() {

}

bool
CBullet::Initialise(short _iType, float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY) {

	// Player Bullet
	if (_iType == 0) {
		VALIDATE(CEntity::Initialise(IDB_BULLET_PLAYER_SPRITE, IDB_BULLET_PLAYER_MASK));
	}
	// Enemy Bullet
	else {
		VALIDATE(CEntity::Initialise(IDB_BULLET_ENEMY_SPRITE, IDB_BULLET_ENEMY_MASK));
	}

	m_fX = _fPosX;
	m_fY = _fPosY;

	m_fVelocityX = _fVelocityX;
	m_fVelocityY = _fVelocityY;

	return (true);
}

void
CBullet::Draw() {
	CEntity::Draw();
}

void
CBullet::Process(float _fDeltaTick) {
	m_fX += m_fVelocityX * _fDeltaTick;
	m_fY += m_fVelocityY * _fDeltaTick;

	CEntity::Process(_fDeltaTick);
}

float
CBullet::GetVelocityX() const {
	return (m_fVelocityX);
}

float
CBullet::GetVelocityY() const {
	return (m_fVelocityY);
}

void
CBullet::SetVelocityX(float _fX) {
	m_fVelocityX = _fX;
}

void
CBullet::SetVelocityY(float _fY) {
	m_fVelocityY = _fY;
}

float
CBullet::GetRadius() const {
	return (GetWidth() / 2.0f);
}
