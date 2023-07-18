#include "stdafx.h"
#include "Shield.h"

CShield::CShield() : m_fDistance(0.f)
{
}

CShield::~CShield()
{
}

void CShield::Initialize()
{
	m_dDelayTime = GetTickCount64();

	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fDistance = 100.f;
	m_fSpeed = 5.f;
}

int CShield::Update()
{
	m_fAngle += m_fSpeed;

	m_tInfo.fX = m_pTarget->Get_Info().fX + m_fDistance * cosf(m_fAngle * (PI / 180.f));
	m_tInfo.fY = m_pTarget->Get_Info().fY - m_fDistance * sinf(m_fAngle * (PI / 180.f));

	__super::Update_Rect();

	if (m_dDelayTime + 5000 < GetTickCount64()) {
		return OBJ_DEAD;
	}
	else
		return OBJ_NOEVENT;
}

void CShield::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShield::Release()
{
}

void CShield::Late_Update()
{
}
