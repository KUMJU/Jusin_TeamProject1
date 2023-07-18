#pragma once
#include "Obj.h"

class CBullet : public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	virtual void Initialize() override;
	virtual int Update() PURE;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Late_Update() override;


protected:
	float m_fDistance;
	float m_fPosition;
	float m_fAngle;
	DIRECTION m_Dir;

};

