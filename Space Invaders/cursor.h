#pragma once

#if !defined(__CURSOR_H__)
#define __CURSOR_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes
class CSprite;

class CCursor : public CEntity {
	// Member Functions
public:
	CCursor();
	CCursor(int _iMaxChoices);
	virtual ~CCursor();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	int GetCursorChoice() const;

protected:

private:
	CCursor(const CCursor& _kr);
	CCursor& operator= (const CCursor& _kr);

	// Member Variables
private:
	int m_iMaxChoices;
	int m_iChoice;
	bool m_bCanMove;
	float m_fCanMoveResetTimer;

};

#endif