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
	m_fSpeed = 15.f;

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
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{
}

