#include "stdafx.h"
#include "Wave.h"

CWave::CWave()
{
}

CWave::~CWave()
{
}

void CWave::Initialize()
{
	m_fSpeed = 100.f;
	m_dDelayTime = GetTickCount64();
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 400.f;
	m_tInfo.fX = 0.f;
	m_tInfo.fY = 300.f;
}

int CWave::Update()
{

	if (m_tRect.right >= 700) {
		return OBJ_DEAD;
	}

	if (m_dDelayTime + 100 > GetTickCount64()) {
		return OBJ_NOEVENT;
	}

	m_tInfo.fX += m_fSpeed;

	__super::Update_Rect();
	m_dDelayTime = GetTickCount64();

	return OBJ_NOEVENT;
}

void CWave::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CWave::Release()
{
}
