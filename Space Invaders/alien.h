#pragma once

#if !defined(__BRICK_H__)
#define __BRICK_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

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

    void SetHit(bool _b);
    bool IsHit() const;

protected:

private:
    CAlien(const CAlien& _kr);
    CAlien& operator= (const CAlien& _kr);

    // Member Variables
public:

protected:
    bool m_bHit;

private:

};

#endif    // __BRICK_H__

