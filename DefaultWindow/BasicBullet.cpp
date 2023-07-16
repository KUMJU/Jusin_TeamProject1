#include "stdafx.h"
#include "BasicBullet.h"

BasicBullet::BasicBullet(DIRECTION _dir, float _position)
{
	m_Dir = _dir;
	m_fPosition = _position;
}

BasicBullet::~BasicBullet()
{
}

int BasicBullet::Update()
{
	if (m_bDead == true) {
		return OBJ_DEAD;
	}

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
	
	__super::Update_Rect();
	return	OBJ_NOEVENT;
}

void BasicBullet::Release()
{
}
