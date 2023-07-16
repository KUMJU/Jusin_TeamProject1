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


protected:
	float m_fDistance;
	float m_fPosition;
	DIRECTION m_Dir;

	/*
	m_fDistance: 총알이 중점으로부터 떨어져 생성될 때 떨어진 거리값
	m_fPosition: 총알이 사용자 기준 왼쪽에 생성되는지 오른쪽에 생성되는지 결정
	*/
};

