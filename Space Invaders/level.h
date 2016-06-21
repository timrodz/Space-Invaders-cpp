#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes
class CBullet;
class CPlayer;
class CAlien;
class CFPSCounter;
class CBackGround;

class CLevel
{
    // Member Functions
public:
    CLevel();
    virtual ~CLevel();

    virtual bool Initialise(int _iWidth, int _iHeight);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    CPlayer* GetPaddle() const;

    int GetAliensRemaining() const;

protected:
    void ProcessBallWallCollision();
	void ProcessPaddleWallCollison();
    void ProcessBallPaddleCollision();
    void ProcessBulletAlienCollision();
	void ProcessBulletPlayerCollision();

    void ProcessCheckForWin();

    void ProcessBallBounds();

    void UpdateScoreText();
    void DrawScore();
	void DrawFPS();

    void SetAliensRemaining(int _i);

private:
    CLevel(const CLevel& _kr);
    CLevel& operator= (const CLevel& _kr);

    // Member Variables
public:

protected:
	CBackGround* m_pBackground;
    CBullet* m_pBullet;
    CPlayer* m_pPlayer;
	std::vector<CBullet*> m_vecPlayerBullets;
	std::vector<CBullet*> m_vecEnemyBullets;
    std::vector<CAlien*> m_vecAliens;
	CFPSCounter* m_fpsCounter;

    int m_iWidth;
    int m_iHeight;

    int m_iAliensRemaining;

    std::string m_strScore;

private:

};

#endif    // __LEVEL_H__