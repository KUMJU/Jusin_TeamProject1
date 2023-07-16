#pragma once
#include "Bullet.h"

class CTripleBullet : public CBullet
{
public:
	CTripleBullet();
	~CTripleBullet();

	virtual void Initialize() override;
	virtual int Update() override;


};

