#pragma once

#if !defined(__BRICK_H__)
#define __BRICK_H__

// Library Includes

// Local Includes
#include "entity.h"


// Types
class CBullet;

// Constants

// Prototypes

class CAlien : public CEntity
{
	// Member Functions
public:
	CAlien();
	virtual ~CAlien();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void DestroyBullet();
	CBullet* GetBullet() const;

	bool GetCanShoot();
	void SetCanShoot();
	void SetBulletReset();

	void SetShipSpeed(float _fSpeed);

	float GetBulletSpeed() const;
	void SetBulletSpeed(float _fSpeed);

	void SetHit(bool _b);
	bool IsHit() const;

protected:

private:
	CAlien(const CAlien& _kr);
	CAlien& operator= (const CAlien& _kr);

	// Member Variables
private:
	CBullet* m_pBullet;
	float m_fSpeed;
	float m_fBulletSpeed;
	bool m_bCanShoot;
	bool m_bBulletHasBeenReset;
	bool m_bHit;

	int m_iAwardedPoints;

};

#endif    // __BRICK_H__

