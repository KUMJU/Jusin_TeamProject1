#include "stdafx.h"
#include "MainGame.h"

CMainGame::CMainGame()
	: m_iStage(1)
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
			}
			else
				++iter;
		}
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


}


void CMainGame::LateUpdate(void)
{
	CCollisionMgr::tempCollision(m_ObjList[OBJ_PLAYER].front(), rc1, BT_BASIC);
	CCollisionMgr::tempCollision(m_ObjList[OBJ_PLAYER].front(), rc2, BT_TWOWAY);
	CCollisionMgr::tempCollision(m_ObjList[OBJ_PLAYER].front(), rc3, BT_TRIPLE);

	CCollisionMgr::tempCollision2(m_ObjList[OBJ_PLAYERBULLET], rc3);


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

