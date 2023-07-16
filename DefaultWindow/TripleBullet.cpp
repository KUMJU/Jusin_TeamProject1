#include "stdafx.h"
#include "TripleBullet.h"

CTripleBullet::CTripleBullet()
{
}

CTripleBullet::~CTripleBullet()
{
}

void CTripleBullet::Initialize()
{
	m_InfoVec.push_back({ m_tInfo.fX - 15, m_tInfo.fY,15.f, 15.f });
	m_InfoVec.push_back({ m_tInfo.fX, m_tInfo.fY,15.f, 15.f });
	m_InfoVec.push_back({ m_tInfo.fX + 15, m_tInfo.fY,15.f, 15.f });

	m_fSpeed = 10.f;

}

int CTripleBullet::Update()
{
	int count(0);

	for (auto& iter : m_InfoVec) {
		if (0 == count) {
			iter.fX -= m_fSpeed;
			iter.fY -= m_fSpeed;
		}
		else if(1 == count) {
			iter.fY -= m_fSpeed;
		}
		else if (2 == count) {
			iter.fX += m_fSpeed;
			iter.fY -= m_fSpeed;
		}
		++count;
	}

	CBullet::UpdateRectList();
	return	OBJ_NOEVENT;
}
