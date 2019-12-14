#include "Enemy.h"
#include <random>

#define DEFAULT_SHOOT_COOLTIME 1.f

Enemy::Enemy()
{
	revolution(90.f, 0.f, 0.f);
}

void Enemy::setEnemyLocation()
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urdX(-35, 35);
	std::uniform_real_distribution<float> urdY(10, 15);

	startX = urdX(dre);
	stopY = urdY(dre);
}

void Enemy::update(float eTime)
{
	Object::update(eTime);
	shootCoolTime -= eTime;
	if (startY > stopY)
		startY -= 10 * eTime;
	turn += eTime * 2;

	setPos(startX, startY, 0);

	setRotate(0, turn, 0);
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