#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	void	Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void	Set_Direction(DIRECTION eDir) { m_eDir = eDir; }


public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()		PURE;
	virtual void		Late_Update();

	INFO	Get_Info() { return m_tInfo; }
	virtual RECT		GetRect();
	void	Set_Dead() { m_bDead = true; }

	void	Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	void	Set_Angle(float _fAngle) { m_fAngle = _fAngle; }


protected:
	 void		Update_Rect();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;

	bool		m_bDead;
	bool		m_bIsPlr;
	float		m_fSpeed;

	float		m_fAngle;
	CObj*		m_pTarget;

};

