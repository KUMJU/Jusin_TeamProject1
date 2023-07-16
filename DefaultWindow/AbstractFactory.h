#pragma once

#include "Obj.h"
#include "Define.h"
#include "BasicBullet.h"
#include"SideBullet.h"

class CAbstractFactory
{
public:

	CAbstractFactory() {};
	~CAbstractFactory() {};

	template<typename T>
	static CObj* CreateObj() {

		CObj* newObj = new T;
		newObj->Initialize();

		return newObj;
	};

	static void CreateBullet(BULLETTYPE _btype, float _fx, float _fy,list<CObj*>* _li , DIRECTION _dir) {
		CObj* newBullet;
		switch (_btype)
		{
		case BT_BASIC:
			_li->push_back(CreateBasic(_dir,_fx,_fy,0.f));
			break;	
		case BT_TWOWAY:
			_li->push_back(CreateBasic(_dir, _fx, _fy, 1.f));
			_li->push_back(CreateBasic(_dir, _fx, _fy, -1.f));
			break;
		case BT_TRIPLE:
			_li->push_back(CreateBasic(_dir, _fx, _fy, 0.f));
			_li->push_back(CreateSide(_dir, _fx, _fy, 1.f));
			_li->push_back(CreateSide(_dir, _fx, _fy, -1.f));
			break;
		default:
				break;
		}
	};

private:

	static CObj* CreateBasic(DIRECTION _dir, float _fx, float _fy, float _distance ) {
		CObj* newBullet = new BasicBullet(_dir, _distance);
		newBullet->Set_Pos(_fx, _fy);
		newBullet->Initialize();

		return newBullet;
	}

	static CObj* CreateSide(DIRECTION _dir, float _fx, float _fy, float _distance) {
		CObj* newBullet = new SideBullet(_dir, _distance);
		newBullet->Set_Pos(_fx , _fy );
		newBullet->Initialize();

		return newBullet;
	}
};