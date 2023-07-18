#pragma once
#include "Obj.h"
#include "Define.h"

class CMouse :
	public CObj
{
public:
	CMouse();
	virtual ~CMouse();
public:

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:

	//const RECT PowerUpBox_1{ OUTLINE + 15, OUTLINE + 30, OUTLINE + 15 + 180, WINCY - (OUTLINE + 20) };
	//const RECT PowerUpBox_2{ OUTLINE + 195 + 15, OUTLINE + 30, OUTLINE + 195 + 15 + 180, WINCY - (OUTLINE + 20) };
	//const RECT PowerUpBox_3{ OUTLINE + 390 + 15, OUTLINE + 30, OUTLINE + 390 + 15 + 180, WINCY - (OUTLINE + 20) };

};

