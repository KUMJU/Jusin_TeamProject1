#include "stdafx.h"
#include "Bomb.h"

CBomb::CBomb() : m_iCount(0)
{
}

CBomb::~CBomb()
{
}

void CBomb::Initialize()
{  
    SetRandomPosition();

}

int CBomb::Update()
{
    if (150 <= m_tInfo.fCX) {
        ++m_iCount;
        SetRandomPosition();
    }

    if (5 == m_iCount) {
        return OBJ_DEAD;
    }

    m_tInfo.fCX += 3.f;
    m_tInfo.fCY += 3.f;

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CBomb::Render(HDC hDC)
{
    

    Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBomb::Release()
{
}

void CBomb::Late_Update()
{

}

void CBomb::SetRandomPosition()
{
    m_tInfo.fCX = 60.f;
    m_tInfo.fCY = 60.f;
    m_tInfo.fX = static_cast<float>((rand() % 450 + 200));
    m_tInfo.fY = static_cast<float>((rand() % 250 + 200));

}
