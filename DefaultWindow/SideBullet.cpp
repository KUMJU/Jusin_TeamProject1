#include "stdafx.h"
#include "SideBullet.h"

SideBullet::SideBullet(DIRECTION _dir, float _position)
{
	m_Dir = _dir;
	m_fPosition = _position;

}

SideBullet::~SideBullet()
{
}

int SideBullet::Update()
{
	if (m_bDead == true) {
		return OBJ_DEAD;
	}

	switch (m_Dir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY -= m_fSpeed * (m_fPosition);
		break;
	case DIR_DOWN:
		m_tInfo.fX += m_fSpeed * (m_fPosition);
		m_tInfo.fY += m_fSpeed;
		break;
	case DIR_RIGHT:
		m_tInfo.fX += m_fSpeed;
		m_tInfo.fY -= m_fSpeed * (m_fPosition);
		break;
	case DIR_UP:
		m_tInfo.fX += (m_fSpeed - 5)*(m_fPosition);
		m_tInfo.fY -= m_fSpeed;
		break;
	default:
		break;
	}


	__super::Update_Rect();
	return	OBJ_NOEVENT;
}

void SideBullet::Release()
{
}
