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

public:
	virtual void		Initialize()	PURE;
	virtual int			Update()		PURE;
	virtual void		Render(HDC hDC)	PURE;
	virtual void		Release()		PURE;
	virtual void		Late_Update();

	virtual RECT		GetRect();
	void	Set_Dead() { m_bDead = true; }

protected:
	 void		Update_Rect();

protected:
	INFO		m_tInfo;
	RECT		m_tRect;

	bool		m_bDead;
	float		m_fSpeed;

};

