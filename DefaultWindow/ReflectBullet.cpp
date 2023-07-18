#include "stdafx.h"
#include "ReflectBullet.h"

ReflectBullet::ReflectBullet(DIRECTION _dir, float _position, bool _isPlr) : m_iCount(0)
{
	m_Dir = _dir;
	m_fPosition = _position;
	m_bIsPlr = _isPlr;
}

ReflectBullet::~ReflectBullet()
{
}

int ReflectBullet::Update()
{

	if (5 == m_iCount) {
		return OBJ_DEAD;
	}


	if (0 == m_iCount) {
		switch (m_Dir)
		{
		case DIR_LEFT:
			m_tInfo.fX -= m_fSpeed;
			break;
		case DIR_DOWN:
			m_tInfo.fY += m_fSpeed;
			break;
		case DIR_RIGHT:
			m_tInfo.fX += m_fSpeed;
			break;
		case DIR_UP:
			m_tInfo.fY -= m_fSpeed;
			break;
		default:
			break;
		}
	}
	else {
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180);
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180);

	}


	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void ReflectBullet::Late_Update()
{

	if (m_tRect.top <= 100) {
		m_tRect.top = 105;
		m_fAngle = -(rand() % 120 + 30);
		m_iCount++;
	}
	else if (m_tRect.bottom >= 500) {
		m_tRect.bottom = WINCY - OUTLINE - 1;
		m_fAngle = (rand() % 120 + 30);
		m_iCount++;
	}
	else if (m_tRect.left <= 100) {
		m_tRect.left = OUTLINE + 1;
		m_fAngle = -(rand() % 80 + 5);
		m_iCount++;
	}
	else if (m_tRect.right >= 700) {
		m_tRect.right = WINCX - OUTLINE - 1;
		m_fAngle = -(rand() % 70 + 80);
		m_iCount++;
	}

}

void ReflectBullet::Release()
{


}

