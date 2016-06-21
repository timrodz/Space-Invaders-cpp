#pragma once

#if !defined(__PADDLE_H__)
#define __PADDLE_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"

// Types

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
	//bool GetSprites(
	void SetHit(bool _b);
	bool IsHit() const;

protected:

private:
    CPlayer(const CPlayer& _kr);
    CPlayer& operator= (const CPlayer& _kr);

    // Member Variables
public:

protected:

private:
	bool m_bHit;
	float m_fShootTimer;
	bool m_bCanShoot;

};

#endif    // __PADDLE_H__
