// Library Includes
#include <ctime> 
// Local Includes
#include "resource.h"
#include "utils.h"
#include "bullet.h"

// This Include
#include "alien.h"

// Static Variables

// Static Function Prototypes

// Implementation

CAlien::CAlien() :
	m_fSpeed(20),
	m_fBulletSpeed(100),
	m_bCanShoot(false),
	m_bBulletHasBeenReset(true),
	m_bHit(false),
	m_bMoveLeft(false),
	m_bMoveRight(false),
	m_bCurrentDirectionRight(true)

{}

CAlien::~CAlien() 
{}

bool CAlien::Initialise() {

	VALIDATE(CEntity::Initialise(IDB_SHIP_ENEMY_SPRITE, IDB_SHIP_ENEMY_MASK));

	return (true);

}

void CAlien::Draw() {

	if (!m_bHit) {

		if (m_pBullet != nullptr)
			m_pBullet->Draw();

		CEntity::Draw();

	}

}

void CAlien::Process(float _fDeltaTick) {

	if (!m_bHit) {

		// Movement

		// Check for direction change
		if (m_bMoveLeft){

			m_bCurrentDirectionRight = false;
			m_fY += GetHeight();
			m_fSpeed += 7;
		}

		else if (m_bMoveRight){
			
			m_bCurrentDirectionRight = true;
			m_fY += GetHeight();
			m_fSpeed += 7;
		}

		// Move based on current direction
		if (m_bCurrentDirectionRight){

			m_fX += m_fSpeed * _fDeltaTick;
		}

		else{

			m_fX -= m_fSpeed * _fDeltaTick;
		}

		// Bullets
		//srand((unsigned int)time(NULL));
		//int x = (rand() % 4);

		//if (x == 2){

			if (m_bCanShoot && m_bBulletHasBeenReset) {
		
				m_pBullet = new CBullet();
				m_pBullet->Initialise(1, m_fX, m_fY, GetBulletSpeed());
				m_bCanShoot = false;
				m_bBulletHasBeenReset = false;			
			}
	//	}

		if (m_pBullet != nullptr)
			m_pBullet->Process(_fDeltaTick);

		CEntity::Process(_fDeltaTick);

	}

}

void CAlien::DestroyBullet() {

	m_bCanShoot = true;
	m_pBullet = nullptr;

}

CBullet* CAlien::GetBullet() const {

	return (m_pBullet);

}

bool CAlien::GetCanShoot() {

	return (m_bCanShoot);

}

void CAlien::SetCanShoot() {

	m_bCanShoot = true;

}

void CAlien::SetBulletReset() {

	m_bBulletHasBeenReset = true;

}

void CAlien::SetShipSpeed(float _fSpeed) {

	m_fSpeed = _fSpeed;

}

float CAlien::GetBulletSpeed() const {

	return (m_fBulletSpeed);

}

void CAlien::SetBulletSpeed(float _fSpeed) {

	m_fBulletSpeed = _fSpeed;
}

void CAlien::SetHit(bool _b) {

	m_bHit = _b;
}

bool CAlien::IsHit() const {

	return (m_bHit);
}

void CAlien::SetMoveLeft(bool _b)
{
	m_bMoveLeft = _b;
}

void CAlien::SetMoveRight(bool _b)
{
	m_bMoveRight = _b;
}

