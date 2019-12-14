#include "Enemy.h"

#define DEFAULT_SHOOT_COOLTIME 1.f

Enemy::Enemy()
{
	revolution(90.f, 0.f, 0.f);
}

void Enemy::update(float eTime)
{
	Object::update(eTime);
	shootCoolTime -= eTime;
}

bool Enemy::canShoot()
{
	if (shootCoolTime < FLT_EPSILON)
		return true;
	return false;
}

void Enemy::resetCoolTime()
{
	shootCoolTime = DEFAULT_SHOOT_COOLTIME;
}
