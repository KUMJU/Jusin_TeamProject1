#pragma once
#include "Obj.h"
class CMonster : public CObj
{
public:
	     CMonster();
virtual ~CMonster();

public:
	virtual void Initailize();
	virtual int Update();
	virtual void Release();
	virtual void Render(HDC hDC);



};

