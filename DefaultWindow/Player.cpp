#include "stdafx.h"
#include "Player.h"
#include "BasicBullet.h"
#include"AbstractFactory.h"
#include"Wave.h"
#include"Bomb.h"
#include "Shield.h"


CPlayer::CPlayer() : m_pBullet(nullptr), m_bType(BT_BASIC), m_debTime(0), m_skillCool(0), m_skillType(ST_WAVE), m_iLife(3), m_Skill_Level(1), m_iPlrState(PS_BASIC) , m_fDistance(0.f)
{
	m_bIsPlr = true;

}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_dSuperArmorTime = GetTickCount64();
	m_PlrColor = RGB(50, 50, 200);
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 50.f, 50.f };
	m_fSpeed = 5.f;
	m_debTime = GetTickCount64();
	m_skillCool = GetTickCount64();
	m_fAngle = 0.f;

}

int CPlayer::Update()
{

	if (m_iLife <= 0) {

		return OBJ_DEAD;

	}

	Key_Input();
	CheckPlayerPosition();

	__super::Update_Rect();

	if (PS_SUPERARMOR == m_iPlrState) {
		if (m_dSuperArmorTime + 1500 < GetTickCount64()) {
			m_iPlrState = PS_BASIC;
			m_PlrColor = RGB(50, 50, 200);
		}
	}

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{

}


void CPlayer::Render(HDC hDC)
{

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(m_PlrColor);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void CPlayer::Release()
{
}

void CPlayer::OnAttacked()
{
	if (PS_SUPERARMOR != m_iPlrState) {
		if (m_iLife > 0) {
			--m_iLife;
			m_iPlrState = PS_SUPERARMOR;
			m_dSuperArmorTime = GetTickCount64();
			m_PlrColor = RGB(255, 0, 0);
		}
	}
}


void CPlayer::CheckPlayerPosition()
{

	if (m_tInfo.fX - 25.f <= 100) {
		m_tInfo.fX = 125.f;
	}
	if (m_tInfo.fX + 25.f >= 700) {
		m_tInfo.fX = WINCX - 125;
	}
	if (m_tInfo.fY - 25.f <= 100) {
		m_tInfo.fY = 125.f;
	}
	if (m_tInfo.fY + 25.f >= 500) {
		m_tInfo.fY = WINCY - 125;
	}

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
			CAbstractFactory::CreateBullet(m_bType, m_tInfo.fX, m_tInfo.fY, m_pBullet, DIR_UP, m_bIsPlr);
			m_debTime = GetTickCount64();
		}
	}

	if (GetAsyncKeyState('A'))
	{
		if (m_debTime + 300 < GetTickCount64()) {
			CAbstractFactory::CreateBullet(m_bType, m_tInfo.fX, m_tInfo.fY, m_pBullet, DIR_LEFT, m_bIsPlr);
			m_debTime = GetTickCount64();
		}
	}

	if (GetAsyncKeyState('S'))
	{
		if (m_debTime + 300 < GetTickCount64()) {
			CAbstractFactory::CreateBullet(m_bType, m_tInfo.fX, m_tInfo.fY, m_pBullet, DIR_DOWN, m_bIsPlr);
			m_debTime = GetTickCount64();
		}
	}
	if (GetAsyncKeyState('D'))
	{
		if (m_debTime + 300 < GetTickCount64()) {
			CAbstractFactory::CreateBullet(m_bType, m_tInfo.fX, m_tInfo.fY, m_pBullet, DIR_RIGHT, m_bIsPlr);
			m_debTime = GetTickCount64();
		}
	}

	if (GetAsyncKeyState('E'))
	{
		if (m_Skill_Level == 1)
		{
			if (m_skillCool + 1000 < GetTickCount64()) {
				m_SkillSlot->push_back(CAbstractFactory::CreateObj<CBomb>());
				m_skillCool = GetTickCount64();
			}
		}
		else if (m_Skill_Level == 2)
		{
			if (m_skillCool + 1000 < GetTickCount64()) {
				m_SkillSlot->push_back(CAbstractFactory::CreateObj<CWave>());
				m_skillCool = GetTickCount64();

			}
		}
	}

	if (GetAsyncKeyState('Q'))
	{
		if (m_skillCool + 1000 < GetTickCount64()) {
			m_SkillSlot->push_back(Create_Shield());
			m_skillCool = GetTickCount64();
		}
	}
}

CObj* CPlayer::Create_Shield()
{
	CObj* pShield = CAbstractFactory::CreateObj<CShield>();

	pShield->Set_Target(this);

	return pShield;
}
