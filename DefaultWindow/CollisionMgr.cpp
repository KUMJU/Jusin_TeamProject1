#include "stdafx.h"
#include "CollisionMgr.h"

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::Check_Sphere(CObj* pDst, CObj* pSrc)
{
	float		fWidth = fabs(pDst->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = fabs(pDst->Get_Info().fY - pSrc->Get_Info().fY);

	float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDst->Get_Info().fCY + pSrc->Get_Info().fCX) * 0.5f;

	return fRadius >= fDiagonal;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> Dst, list<CObj*> Src)
{
	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (Check_Sphere(DstList, SrcList))
			{
				DstList->Set_Dead();
				SrcList->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::PlayerCollision(CObj* Dst, list<CObj*> Src)
{
	for (auto& SrcList : Src)
	{
		if (Check_Sphere(Dst, SrcList))
		{
			dynamic_cast<CPlayer*>(Dst)->OnAttacked();
		}
	}
}

void CCollisionMgr::SkillCollision(list < CObj*> Dst, list<CObj*> Src)
{
	for (auto& DstList : Dst)
	{
		for (auto& SrcList : Src)
		{
			if (Check_Sphere(DstList, SrcList))
			{
				SrcList->Set_Dead();
			}
		}
	}
}
