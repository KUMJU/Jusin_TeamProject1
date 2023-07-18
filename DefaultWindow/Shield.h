#pragma once
#include"Skill.h"

class CShield : public CSkill
{
public:
	CShield();
	~CShield();
	
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Late_Update();
	
private:
	float			m_fDistance;

};

