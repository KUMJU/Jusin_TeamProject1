#pragma once
#include "Obj.h"
class CMonster 
	: public CObj
{
public:
	CMonster(int _type);
	virtual ~CMonster();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void Set_PlrList(CObj* _plrList) { m_PlrList = _plrList; };
	void Set_BulletList(list<CObj*>* _bList) { m_mBulletList = _bList; }

private:

	CObj*	m_PlrList;
	list<CObj*>* m_mBulletList;
	int		m_iMType;

	DWORD m_delayTime;

};

