#include "stdafx.h"
#include "MainGame.h"

CMainGame::CMainGame()
	: m_iStage(1), m_iMissionCount(0), m_iMission_TargetCount(15), m_bMissionClear(false), m_iPowerSelect(0), m_iPowerLevel_Bullet(1), m_iPowerLevel_Quality(1) , m_iCurrentState(GS_PLAYING)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	if(m_ObjList[OBJ_PLAYER].empty())
	{ 
		m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory::CreateObj<CPlayer>());
	}	
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_PLAYERBULLET]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Skill(&m_ObjList[OBJ_SKILL]);
	
	m_ObjList[OBJ_MOUSE].push_back(CAbstractFactory::CreateObj<CMouse>());


}

int CMainGame::Update(void)
{
	if (GS_GAMEOVER == m_iCurrentState) {
		return GS_GAMEOVER;
	}


	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList [i].begin();
			iter != m_ObjList[i].end(); )
		{
			int	iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				if (i == OBJ_PLAYER) {
					m_iCurrentState = GS_GAMEOVER;
					return GS_GAMEOVER;
				}
				else{
					Safe_Delete<CObj*>(*iter);
					iter = m_ObjList[i].erase(iter);

					if (i == OBJ_MONSTER) // 사망처리된 오프젝트가 몬스터일때 미션카운팅
					{
						++m_iMissionCount;

						if (m_iMissionCount == m_iMission_TargetCount)
						{
							++m_iStage;
							if (m_iStage == 4)
							{
								m_iCurrentState = GS_GAMEOVER;
								return GS_GAMEOVER;
							}
							m_bMissionClear = true;
							ReleaseMonster();						
							m_iMission_TargetCount += 10;
							m_iMissionCount = 0;
							break;
						}
					}
				}
			}
			else
				++iter;
		}
	}

	if (m_bMissionClear)
	{
		CheckChoice();
		PowerUpManager();

	}

	if (!m_bMissionClear) //레밸업 이벤트떄는 몬스터 생성x
	{
		CreateMonster();
	}

	return GS_PLAYING;
}

void CMainGame::Render(void)
{

	if (GS_PLAYING == m_iCurrentState) {
		Rectangle(m_DC, 0, 0, WINCX, WINCY);

		for (size_t i = 0; i < OBJ_MOUSE; ++i)
		{
			for (auto& iter : m_ObjList[i])
				iter->Render(m_DC);
		}

		Rectangle(m_DC, 0, 0, 100, WINCY);
		Rectangle(m_DC, WINCX - 100, 0, WINCX, WINCY);
		Rectangle(m_DC, 0, 0, WINCX, 100);
		Rectangle(m_DC, 0, 500, WINCX, WINCY);

		RendChoiceBox();

		for (auto& iter : m_ObjList[OBJ_MOUSE])
			iter->Render(m_DC);

		RendMission(1);

		TCHAR		szLife[32] = L"";

		wsprintf(szLife, L"라이프:");
		TextOut(m_DC, 10, 30, szLife, lstrlen(szLife));

		wsprintf(szLife, L"%d", dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->GetLife());
		TextOut(m_DC, 65, 30, szLife, lstrlen(szLife));
	}
	else {

		Rectangle(m_DC, 0, 0, WINCX, WINCY);
		TCHAR		szGameOver[32] = L"Game Over!";
		TextOut(m_DC, WINCX*0.5f-50.f, WINCY*0.5, szGameOver, lstrlen(szGameOver));

	}


}


void CMainGame::LateUpdate(void)
{

	if (GS_GAMEOVER == m_iCurrentState) {

		return;
	}

	CCollisionMgr::SkillCollision(m_ObjList[OBJ_SKILL], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::SkillCollision(m_ObjList[OBJ_SKILL], m_ObjList[OBJ_MOSTERBULLET]);

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}


	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_PLAYERBULLET], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::PlayerCollision(m_ObjList[OBJ_PLAYER].front(), m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::PlayerCollision(m_ObjList[OBJ_PLAYER].front(), m_ObjList[OBJ_MOSTERBULLET]);

}

void CMainGame::RendMission(int _Stage)
{
	TCHAR		szMission[32] = L"";

	wsprintf(szMission, L"STAGE %d", m_iStage);
	TextOut(m_DC, 10, 10, szMission, lstrlen(szMission));
	wsprintf(szMission, L"미션 : 몬스터 처치");
	TextOut(m_DC, 10, 50, szMission, lstrlen(szMission));

	switch (_Stage)
	{
	case 1:
		wsprintf(szMission, L"%d / %d", m_iMissionCount, m_iMission_TargetCount);
		TextOut(m_DC, 10, 70, szMission, lstrlen(szMission));
		break;

	case 2:
		break;

	case 3:
		break;

	}
}

void CMainGame::RendChoiceBox()
{

	if (m_bMissionClear)
	{
		Rectangle(m_DC, 600, 15, 670, 85);
		Rectangle(m_DC, 680, 15, 750, 85);

		TCHAR	szMission[32] = L"Add Bullet";
		RECT	rc{ 602, 15, 670, 85 };
		DrawText(m_DC, szMission, lstrlen(szMission), &rc, DT_VCENTER | DT_SINGLELINE);

		TCHAR	szMission_2[32] = L"Power Up";
		RECT	rc_2{ 685, 15, 750, 85 };
		DrawText(m_DC, szMission_2, lstrlen(szMission_2), &rc_2, DT_VCENTER | DT_SINGLELINE);
	}

}

void CMainGame::CheckChoice()
{
	if (GetAsyncKeyState(MK_LBUTTON))
	{
		POINT	ptMouse{};

		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		float fX = (float)ptMouse.x;
		float fY = (float)ptMouse.y;


		if ((600 < fX) && (fX < 670) && (15 < fY) && (fY < 85))
		{
			m_bMissionClear = false;
			m_iPowerSelect = 1;

		}
		else if ((680 < fX) && (fX < 750) && (15 < fY) && (fY < 85))
		{
			m_bMissionClear = false;
			m_iPowerSelect = 2;
		}
	}
}

void CMainGame::ReleaseMonster()
{
	if (!m_ObjList[OBJ_MONSTER].empty()) {
		for_each(m_ObjList[OBJ_MONSTER].begin(), m_ObjList[OBJ_MONSTER].end(), DeleteObj());
		m_ObjList[OBJ_MONSTER].clear();
	}


	if (!m_ObjList[OBJ_MOSTERBULLET].empty()) {
		for_each(m_ObjList[OBJ_MOSTERBULLET].begin(), m_ObjList[OBJ_MOSTERBULLET].end(), DeleteObj());
		m_ObjList[OBJ_MOSTERBULLET].clear();
	}
}

void CMainGame::CreateMonster()
{

	if (rand() % 1000 < 4)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory::Create_Obj<CMonster>(rand() % (WINCX - (OUTLINE * 2) - (50)) + OUTLINE + 25, OUTLINE * 0.5f, rand() % m_iStage + 1));
		dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_PlrList(m_ObjList[OBJ_PLAYER].front());
		dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_BulletList(&m_ObjList[OBJ_MOSTERBULLET]);
	}
	if (rand() % 1000 < 4)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory::Create_Obj<CMonster>(OUTLINE * 0.5f, rand() % (WINCY - (OUTLINE * 2) - (50)) + OUTLINE + 25, rand() % m_iStage + 1));
		dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_PlrList(m_ObjList[OBJ_PLAYER].front());
		dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_BulletList(&m_ObjList[OBJ_MOSTERBULLET]);
	}
	if (rand() % 1000 < 4)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory::Create_Obj<CMonster>(rand() % (WINCX - (OUTLINE * 2) - (50)) + OUTLINE + 25, WINCY - (OUTLINE * 0.5f), rand() % m_iStage + 1));
		dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_PlrList(m_ObjList[OBJ_PLAYER].front());
		dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_BulletList(&m_ObjList[OBJ_MOSTERBULLET]);
	}
	if (rand() % 1000 < 4)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory::Create_Obj<CMonster>(WINCX - (OUTLINE * 0.5f), rand() % (WINCY - (OUTLINE * 2) - (50)) + OUTLINE + 25, rand() % m_iStage + 1));
		dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_PlrList(m_ObjList[OBJ_PLAYER].front());
		dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_BulletList(&m_ObjList[OBJ_MOSTERBULLET]);
	}
}

void CMainGame::PowerUpManager()
{
	if (m_iPowerSelect == 1)
	{
		++m_iPowerLevel_Bullet;
	}
	else if (m_iPowerSelect == 2)
	{
		++m_iPowerLevel_Quality;
	}

	if (m_iStage == 2)
	{
		if (m_iPowerLevel_Bullet == 1 && m_iPowerLevel_Quality == 2)
		{
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_BulletType(BT_REF_BASIC);
			m_iPowerSelect = 0;
		}
		else if (m_iPowerLevel_Bullet == 2 && m_iPowerLevel_Quality == 1)
		{
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_BulletType(BT_TWOWAY);
			m_iPowerSelect = 0;
		}
	}
	else if (m_iStage == 3)
	{
		if (m_iPowerLevel_Bullet == 1 && m_iPowerLevel_Quality == 3)
		{
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->UP_SkillLevel();
		}
		else if (m_iPowerLevel_Bullet == 2 && m_iPowerLevel_Quality == 2)
		{
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_BulletType(BT_REF_TWOWAY);
			m_iPowerSelect = 0;
		}
		else if (m_iPowerLevel_Bullet == 3 && m_iPowerLevel_Quality == 1)
		{
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_BulletType(BT_TRIPLE);
			m_iPowerSelect = 0;
		}

	}
}

void CMainGame::Release(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), DeleteObj());
		m_ObjList[i].clear();
	}

	ReleaseDC(g_hWnd, m_DC);
}

