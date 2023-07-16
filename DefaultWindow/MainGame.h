#pragma once

#include "Define.h"
#include "Player.h"
#include "AbstractFactory.h"
#include"CollisionMgr.h"

class CMainGame
{

public:
	CMainGame();
	~CMainGame();
public:
	void		Initialize(void);
	void		Update(void);
	void		Render(void);
	void		Release(void);
	void		LateUpdate(void);

private:
	list<CObj*>		m_ObjList[OBJ_END];
	int             m_iStage;

	HDC			m_DC;


private:
	//test
	RECT		rc1{200,150,230,180};
	RECT		rc2{300,150,330,180};
	RECT		rc3{ 400,150,430,180 };
	//

};
