#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void	Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }
	void	Set_BulletType(BULLETTYPE _btype) { m_bType = _btype; };
	void	Set_Skill(list<CObj*>* _skill) { m_SkillSlot = _skill; };
	void	OnAttacked();
	void	CheckPlayerPosition();
	int		GetLife() { return m_iLife; };

private:
	void	Key_Input(void);

private:
	list<CObj*>*		m_pBullet;
	list<CObj*>*		m_SkillSlot;

	BULLETTYPE			m_bType;
	SKILLTYPE			m_skillType;
	DWORD				m_debTime;
	DWORD				m_skillCool;
	DWORD				m_dSuperArmorTime;

	int					m_iLife;
	COLORREF			m_PlrColor;


};

