#pragma once

#include"Obj.h"
#include"Player.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

	static void tempCollision(CObj* _plr, RECT _rc,BULLETTYPE _btype) {

		RECT rc{};
		if (IntersectRect(&rc, &(_plr->GetRect()), &_rc)) {
			dynamic_cast<CPlayer*>(_plr)->Set_BulletType(_btype);
		}

	}

	static void tempCollision2(list<CObj*> _li, RECT _rc) {

		RECT rc{};

		for (auto& j : _li) {
			if (IntersectRect(&rc, &(j->GetRect()), &_rc)) {
				j->Set_Dead();
			}
		}

	}
};

