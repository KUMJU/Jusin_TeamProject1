#pragma once

#include"Obj.h"

class CSkill : public CObj
{
public:
	CSkill();
	virtual ~CSkill();

	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() override;

protected:

	DWORD m_dDelayTime;

};

