#pragma once

#include"Obj.h"
#include"Player.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

	static bool	Check_Sphere(CObj* pDst, CObj* pSrc);
	static void Collision_Sphere(list<CObj*> Dst, list<CObj*> Src);
	static void PlayerCollision(CObj* Dst, list<CObj*> Src);

};

