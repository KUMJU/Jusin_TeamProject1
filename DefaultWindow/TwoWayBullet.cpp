#include "stdafx.h"
#include "TwoWayBullet.h"

TwoWayBullet::TwoWayBullet()
{
}

TwoWayBullet::~TwoWayBullet()
{
}

void TwoWayBullet::Initialize()
{
	m_InfoVec.push_back({ m_tInfo.fX - 15, m_tInfo.fY,15.f, 15.f });
	m_InfoVec.push_back({ m_tInfo.fX + 15, m_tInfo.fY,15.f, 15.f });

	m_fSpeed = 10.f;
}

int TwoWayBullet::Update()
{
	for (auto& iter : m_InfoVec) {
		iter.fY -= m_fSpeed;
	}

	CBullet::UpdateRectList();
	return	OBJ_NOEVENT;
}
