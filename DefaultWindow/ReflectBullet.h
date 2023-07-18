#pragma once
#include "Bullet.h"
class ReflectBullet :
    public CBullet
{
public:
    ReflectBullet(DIRECTION _dir, float _position, bool _isPlr);
    ~ReflectBullet();

public:
    virtual int Update() override;
    virtual void Release() override;
    virtual void Late_Update() override;

private:

    int m_iCount;



};

