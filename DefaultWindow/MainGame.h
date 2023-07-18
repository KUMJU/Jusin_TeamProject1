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
	void		RendChoiceBox();	// �Ŀ��� ����â ǥ��
	void		CheckChoice();	// �Ŀ��� üũ
	void		ReleaseMonster(); // ���� ����
	void		CreateMonster(); // ���� ����
	void		PowerUpManager(); // �Ŀ��� ����



private:
	list<CObj*>		m_ObjList[OBJ_END];
	int             m_iStage;
	int				m_iMissionCount;
	int				m_iMission_TargetCount;
	bool			m_bMissionClear;
	int				m_iPowerSelect;
	int				m_iPowerLevel_Bullet, m_iPowerLevel_Quality;

	HDC				m_DC;

};
