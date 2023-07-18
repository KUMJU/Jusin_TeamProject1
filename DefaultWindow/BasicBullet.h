#pragma once

#include"Bullet.h"

class BasicBullet: public CBullet
{
public:
	BasicBullet(DIRECTION _dir, float _position, bool _isPlr);
	virtual ~BasicBullet();

public:
	virtual int Update() override;
	virtual void Release() override;
	

};

