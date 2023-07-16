#pragma once
#include"Obj.h"

class Field : public CObj
{
public:

	Field();
	~Field();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	list<RECT> m_liWall;

};

