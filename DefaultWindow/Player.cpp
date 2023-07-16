#include "stdafx.h"
#include "Player.h"
#include "BasicBullet.h"
#include"AbstractFactory.h"
#include"Wave.h"
#include"Bomb.h"

CPlayer::CPlayer() : m_pBullet(nullptr) , m_bType(BT_BASIC), m_debTime(0) , m_skillCool(0) , m_skillType(ST_WAVE)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 50.f, 50.f };
	m_fSpeed = 5.f;
	m_debTime = GetTickCount64();
	m_skillCool = GetTickCount64();
}

int CPlayer::Update()
{
	Key_Input();

   __super::Update_Rect();

   return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
}


void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input(void)
{	
	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

	if (GetAsyncKeyState('W'))
	{
		if (m_debTime + 300 < GetTickCount64()) {
			CAbstractFactory::CreateBullet(m_bType, m_tInfo.fX, m_tInfo.fY,m_pBullet,DIR_UP);
			m_debTime = GetTickCount64();
		}	
	}

	if (GetAsyncKeyState('A'))
	{
		if (m_debTime + 300 < GetTickCount64()) {
			CAbstractFactory::CreateBullet(m_bType, m_tInfo.fX, m_tInfo.fY, m_pBullet,DIR_LEFT);
			m_debTime = GetTickCount64();
		}
	}

	if (GetAsyncKeyState('S'))
	{
		if (m_debTime + 300 < GetTickCount64()) {
			CAbstractFactory::CreateBullet(m_bType, m_tInfo.fX, m_tInfo.fY, m_pBullet,DIR_DOWN);
			m_debTime = GetTickCount64();
		}
	}
	if (GetAsyncKeyState('D'))
	{
		if (m_debTime + 300 < GetTickCount64()) {
			CAbstractFactory::CreateBullet(m_bType, m_tInfo.fX, m_tInfo.fY, m_pBullet,DIR_RIGHT);
			m_debTime = GetTickCount64();
		}
	}

	if (GetAsyncKeyState('R'))
	{
		if (m_skillCool + 1000 < GetTickCount64()) {
			m_SkillSlot->push_back(CAbstractFactory::CreateObj<CWave>());
			m_skillCool = GetTickCount64();

		}
	}

}