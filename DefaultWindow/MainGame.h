#pragma once

#include "Define.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "CMonster.h"
#include "Mouse.h"


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

public:
	void		RendMission(int _Stage); // �̼� ǥ�� �Լ�
	void		MissionCount(); // �̼� ī��Ʈ �Լ�
	void		RendChoiceBox();	// �Ŀ��� ����â ǥ��
	int			CheckChoice();	// �Ŀ��� üũ
	void		ReleaseMonster(); // ���� ����


private:
	list<CObj*>		m_ObjList[OBJ_END];
	int             m_iStage;
	int				m_iMissionCount;
	int				m_iMission_TargetCount;
	bool			m_bMissionClear;
	int				m_iPowerSelect;

	HDC				m_DC;

private:
	//test
	//RECT		rc1{200,150,230,180};
	//RECT		rc2{300,150,330,180};
	//RECT		rc3{400,150,430,180};
	//

};
