#pragma once

#include "Obj.h"
#include "Define.h"
#include "BasicBullet.h"
#include"SideBullet.h"
#include"ReflectBullet.h"

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

	template<typename T>
	static CObj* Create_Obj(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}

	template<typename T>
	static CObj* Create_Obj(float _fX, float _fY, int _type)
	{
		CObj* pObj = new T(_type);
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}


	static void CreateBullet(BULLETTYPE _btype, float _fx, float _fy, list<CObj*>* _li, DIRECTION _dir, bool _isPlr) {
		CObj* newBullet;
		switch (_btype)
		{
		case BT_BASIC:
			_li->push_back(CreateBasic(_dir, _fx, _fy, 0.f, _isPlr));
			break;
		case BT_TWOWAY:
			_li->push_back(CreateBasic(_dir, _fx, _fy, 1.f, _isPlr));
			_li->push_back(CreateBasic(_dir, _fx, _fy, -1.f, _isPlr));
			break;
		case BT_TRIPLE:
			_li->push_back(CreateBasic(_dir, _fx, _fy, 0.f, _isPlr));
			_li->push_back(CreateSide(_dir, _fx, _fy, 1.f, _isPlr));
			_li->push_back(CreateSide(_dir, _fx, _fy, -1.f, _isPlr));
			break;
		case BT_REF_BASIC:
			_li->push_back(CreateRef(_dir, _fx, _fy, 0.f, _isPlr));
			break;
		case BT_REF_TWOWAY:
			_li->push_back(CreateRef(_dir, _fx, _fy, 1.f, _isPlr));
			_li->push_back(CreateRef(_dir, _fx, _fy, -1.f, _isPlr));
			break;
		default:
			break;
		}
	};

private:

	static CObj* CreateBasic(DIRECTION _dir, float _fx, float _fy, float _distance, bool _isPlr) {
		CObj* newBullet = new BasicBullet(_dir, _distance, _isPlr);
		newBullet->Set_Pos(_fx, _fy);
		newBullet->Initialize();

		return newBullet;
	}

	static CObj* CreateSide(DIRECTION _dir, float _fx, float _fy, float _distance, bool _isPlr) {
		CObj* newBullet = new SideBullet(_dir, _distance, _isPlr);
		newBullet->Set_Pos(_fx, _fy);
		newBullet->Initialize();

		return newBullet;
	}

	static CObj* CreateRef(DIRECTION _dir, float _fx, float _fy, float _distance, bool _isPlr) {
		CObj* newBullet = new ReflectBullet(_dir, _distance, _isPlr);
		newBullet->Set_Pos(_fx, _fy);
		newBullet->Initialize();

		return newBullet;
	}
};