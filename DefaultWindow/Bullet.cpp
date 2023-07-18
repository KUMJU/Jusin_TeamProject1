#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet() :m_fDistance(15.f),m_fPosition(0.f),m_Dir(DIR_UP)
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 15.f;
	m_tInfo.fCY = 15.f;

	if (m_bIsPlr) {
		m_fSpeed = 15.f;
	}
	else {
		m_fSpeed = 3.f;
	}
	switch (m_Dir)
	{
	case DIR_LEFT:
		m_tInfo.fY = m_tInfo.fY + (m_fDistance * m_fPosition);
		break;
	case DIR_DOWN:
		m_tInfo.fX = m_tInfo.fX + (m_fDistance * m_fPosition);
		break;
	case DIR_RIGHT:
		m_tInfo.fY = m_tInfo.fY + (m_fDistance * m_fPosition);
		break;
	case DIR_UP:
		m_tInfo.fX = m_tInfo.fX + (m_fDistance * m_fPosition);
		break;
	default:
		break;
	}
}

void CBullet::Render(HDC hDC)
{
	if (true == m_bIsPlr) {
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
	else {
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CBullet::Release()
{
}

void CBullet::Late_Update()
{
	if (m_tRect.left <= 100 || m_tRect.top <= 100 ||
		m_tRect.right >= WINCX - 100 || m_tRect.bottom >= WINCY - 100) {

		__super::Set_Dead();
	}
}

