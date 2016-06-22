#pragma once

#if !defined(__BALL_H__)
#define __BALL_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes
class CSprite;

class CBullet : public CEntity
{
    // Member Functions
public:
    CBullet();
    virtual ~CBullet();

    bool Initialise(short _iType, float _fPosX, float _fPosY, float _fVelocityY);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    float GetVelocityY() const;
    void SetVelocityY(float _fY);

    float GetRadius() const;

private:
    CBullet(const CBullet& _kr);
    CBullet& operator= (const CBullet& _kr);

    // Member Variables
public:

protected:
    float m_fVelocityY;

private:
	int m_iType;

};

#endif    // __BALL_H__
