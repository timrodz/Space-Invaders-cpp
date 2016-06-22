#pragma once

#if !defined(__PADDLE_H__)
#define __PADDLE_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"

// Types
class CBullet;

// Constants

// Prototypes
class CPlayer : public CEntity
{
	// Member Functions
public:
	CPlayer();
	virtual ~CPlayer();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	bool CheckSprite(int _iResourceID, int _iMaskResourceID);

	void DestroyBullet();
	CBullet* GetBullet() const;

	void SetShipSpeed(float _fSpeed);

	float GetBulletSpeed() const;
	void SetBulletSpeed(float _fSpeed);

	void SetHit(bool _b);
	bool IsHit() const;

private:
	CPlayer(const CPlayer& _kr);
	CPlayer& operator= (const CPlayer& _kr);

	// Member Variables
private: 
	CBullet* m_pBullet;
	float m_fSpeed;
	float m_fBulletSpeed;
	bool m_bCanShoot;
	bool m_bHit;

};

#endif    // __PADDLE_H__
