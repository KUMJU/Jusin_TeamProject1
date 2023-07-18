#include "stdafx.h"
#include "CMonster.h"
#include"AbstractFactory.h"

CMonster::CMonster(int _type) :m_iMType(_type) , m_PlrList(nullptr) , m_mBulletList(nullptr) , m_delayTime(0)
{
}

CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	m_tInfo = { 0.f, 0.f, 50.f, 50.f };
	m_fSpeed = 2.f;
	m_delayTime = GetTickCount64();
}

int CMonster::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	float fDistanceX = m_PlrList->Get_Info().fX - m_tInfo.fX;
	float fDistanceY = m_PlrList->Get_Info().fY - m_tInfo.fY;
	float fDistance = sqrtf(fDistanceX * fDistanceX + fDistanceY * fDistanceY); 

	float fAngle = acosf(fDistanceX / fDistance);

	if (m_tInfo.fY > m_PlrList->Get_Info().fY) {
		fAngle *= -1.f;
	}

	m_tInfo.fX += m_fSpeed * cosf(fAngle);
	m_tInfo.fY += m_fSpeed * sinf(fAngle);

	if (m_delayTime + 1000 < GetTickCount64()) {
		if (2 == m_iMType) {
			CAbstractFactory::CreateBullet(BT_BASIC, m_tInfo.fX, m_tInfo.fY, m_mBulletList, DIR_LEFT, false);
			CAbstractFactory::CreateBullet(BT_BASIC, m_tInfo.fX, m_tInfo.fY, m_mBulletList, DIR_RIGHT, false);
		}
		else if (3 == m_iMType) {
			CAbstractFactory::CreateBullet(BT_BASIC, m_tInfo.fX, m_tInfo.fY, m_mBulletList, DIR_UP, false);
			CAbstractFactory::CreateBullet(BT_BASIC, m_tInfo.fX, m_tInfo.fY, m_mBulletList, DIR_DOWN, false);
			CAbstractFactory::CreateBullet(BT_BASIC, m_tInfo.fX, m_tInfo.fY, m_mBulletList, DIR_LEFT, false);
			CAbstractFactory::CreateBullet(BT_BASIC, m_tInfo.fX, m_tInfo.fY, m_mBulletList, DIR_RIGHT, false);
		}
		m_delayTime = GetTickCount64();
	}

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
}

void CMonster::Release()
{
}

void CMonster::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}
