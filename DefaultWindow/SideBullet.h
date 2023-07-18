#pragma once
#include"Bullet.h"

class SideBullet : public CBullet
{
public:

	SideBullet(DIRECTION _dir, float _position, bool _isPlr);
	~SideBullet();

public:
	virtual int Update() override;
	virtual void Release() override;

private:

};

