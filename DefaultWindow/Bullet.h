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
	m_fDistance: �Ѿ��� �������κ��� ������ ������ �� ������ �Ÿ���
	m_fPosition: �Ѿ��� ����� ���� ���ʿ� �����Ǵ��� �����ʿ� �����Ǵ��� ����
	*/
};

