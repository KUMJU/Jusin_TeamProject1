#include "stdafx.h"
#include "CMonster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::Initailize()
{
	m_tInfo = { 100.f, 100.f, 50.f, 50.f };
	m_fSpeed = 5.f;
}

int CMonster::Update()
{
	return OBJ_NOEVENT;
}

void CMonster::Release()
{
}

void CMonster::Render(HDC hDC)
{
}
