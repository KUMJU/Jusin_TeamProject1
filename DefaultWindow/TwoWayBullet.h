#pragma once
#include"Bullet.h"

class TwoWayBullet : public CBullet
{
public:
	TwoWayBullet();
	~TwoWayBullet();

	virtual void Initialize() override;
	virtual int Update() override;


};

