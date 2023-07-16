#pragma once
#include"Skill.h"

class CBomb : public CSkill
{
public: 
	CBomb();
	~CBomb();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void Late_Update();

private:

	void SetRandomPosition();

private:
	int m_iCount;

};

