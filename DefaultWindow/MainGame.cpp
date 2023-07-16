#include "stdafx.h"
#include "MainGame.h"

CMainGame::CMainGame()
	: m_iStage(1), m_iMissionCount(0), m_iMission_TargetCount(30), m_bMissionClear(false)
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

}

void CMainGame::Update(void)
{

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int	iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);

				if (i == OBJ_MONSTER) // 사망처리된 오프젝트가 몬스터일때 미션카운팅
					++m_iMissionCount;
			}
			else
				++iter;
		}
	}
	if (rand() % 200 < 1)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory::Create_Obj<CMonster>(rand() % (WINCX - (OUTLINE * 2) - (50)) + OUTLINE + 25, OUTLINE * 0.5f, DIR_DOWN));
	}
	if (rand() % 200 < 1)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory::Create_Obj<CMonster>(OUTLINE * 0.5f, rand() % (WINCY - (OUTLINE * 2) - (50)) + OUTLINE + 25, DIR_RIGHT));
	}
	if (rand() % 200 < 1)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory::Create_Obj<CMonster>(rand() % (WINCX - (OUTLINE * 2) - (50)) + OUTLINE + 25, WINCY - (OUTLINE * 0.5f), DIR_UP));
	}
	if (rand() % 200 < 1)
	{
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory::Create_Obj<CMonster>(WINCX - (OUTLINE * 0.5f), rand() % (WINCY - (OUTLINE * 2) - (50)) + OUTLINE + 25, DIR_LEFT));
	}
	LateUpdate();

}

void CMainGame::Render(void)
{

	Rectangle(m_DC, 0, 0, WINCX, WINCY);

	Rectangle(m_DC, rc1.left , rc1.top, rc1.right, rc1.bottom);
	Rectangle(m_DC, rc2.left, rc2.top, rc2.right, rc2.bottom);
	Rectangle(m_DC, rc3.left, rc3.top, rc3.right, rc3.bottom);


	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_DC);
	}


	Rectangle(m_DC, 0, 0,100, WINCY);
	Rectangle(m_DC, WINCX - 100, 0, WINCX, WINCY);
	Rectangle(m_DC, 0, 0, WINCX, 100);
	Rectangle(m_DC, 0, 500, WINCX, WINCY);

	RendMission(1);



}


void CMainGame::LateUpdate(void)
{

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}

	CCollisionMgr::tempCollision(m_ObjList[OBJ_PLAYER].front(), rc1, BT_BASIC);
	CCollisionMgr::tempCollision(m_ObjList[OBJ_PLAYER].front(), rc2, BT_TWOWAY);
	CCollisionMgr::tempCollision(m_ObjList[OBJ_PLAYER].front(), rc3, BT_TRIPLE);
	CCollisionMgr::tempCollision2(m_ObjList[OBJ_PLAYERBULLET], rc3);

	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_PLAYERBULLET], m_ObjList[OBJ_MONSTER]);



}

void CMainGame::RendMission(int _Stage)
{
	TCHAR		szMission[32] = L"";

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

void CMainGame::Release(void)
{
	//Safe_Delete<CObj*>(m_ObjList[OBJ_PLAYER].front());

	//for_each(m_ObjList[OBJ_PLAYERBULLET].begin(), m_ObjList[OBJ_PLAYERBULLET].end(), DeleteObj());
	//m_ObjList[OBJ_PLAYERBULLET].clear();

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), DeleteObj());
		m_ObjList[i].clear();
	}

	ReleaseDC(g_hWnd, m_DC);
}

