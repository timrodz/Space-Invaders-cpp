// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"
#include "backbuffer.h"
#include "game.h"
#include "sprite.h"

// This Include
#include "cursor.h"

#define Y_POS_MOVE 78

// Implementation
CCursor::CCursor()
	: m_iChoice(1)
	, m_bCanMove(true)
	, m_fCanMoveResetTimer(0.0f)
	, m_iMaxChoices(1)
{}

CCursor::CCursor(int _iMaxChoices)
	: m_iChoice(1)
	, m_bCanMove(true)
	, m_fCanMoveResetTimer(0.0f) 
	, m_iMaxChoices(_iMaxChoices)
{}

CCursor::~CCursor() {}

bool
CCursor::Initialise() {

	VALIDATE(CEntity::Initialise(IDB_CURSOR_1, IDB_CURSOR_MASK));

	return (true);

}

void
CCursor::Draw() {

	CEntity::Draw();

}

void
CCursor::Process(float _fDeltaTick) {

	if (m_bCanMove && GetAsyncKeyState(VK_UP) & 0x8000) {

		m_bCanMove = false;

		m_iChoice--;
		m_fY -= Y_POS_MOVE;

	}
	else if (m_bCanMove && GetAsyncKeyState(VK_DOWN) & 0x8000) {

		m_bCanMove = false;

		m_iChoice++;
		m_fY += Y_POS_MOVE;

	}

	if (!m_bCanMove) {

		m_fCanMoveResetTimer += _fDeltaTick;

		if (m_fCanMoveResetTimer > 0.1f) {
			
			m_fCanMoveResetTimer = 0.0f;
			m_bCanMove = true;

		}

	}

	// If the cursor exceeds its limits,
	// Start from the opposite side
	if (m_iChoice < 1) {

		m_iChoice = m_iMaxChoices;

		m_fY += Y_POS_MOVE * (m_iMaxChoices);

	}
	else if (m_iChoice > m_iMaxChoices) {

		m_iChoice = 1;

		m_fY -= Y_POS_MOVE * (m_iMaxChoices);

	}

	CEntity::Process(_fDeltaTick);

}

int CCursor::GetCursorChoice() const {

	return (m_iChoice);

}