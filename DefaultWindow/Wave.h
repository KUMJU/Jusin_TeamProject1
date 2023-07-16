#pragma once
#include"Skill.h"

class CWave : public CSkill
{
public: 
	CWave();
	~CWave();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

};

