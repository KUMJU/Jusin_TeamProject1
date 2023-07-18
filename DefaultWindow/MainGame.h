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
	void		RendMission(int _Stage); // 미션 표기 함수
	void		RendChoiceBox();	// 파워업 선택창 표기
	void		CheckChoice();	// 파워업 체크
	void		ReleaseMonster(); // 몬스터 전멸
	void		CreateMonster(); // 몬스터 생성
	void		PowerUpManager(); // 파워업 관리



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
