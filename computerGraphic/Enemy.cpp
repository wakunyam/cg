#include "Enemy.h"
#include <random>

Enemy::Enemy()
{
	revolution(90.f, 0.f, 0.f);
	
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urdX(-35, 35);
	std::uniform_real_distribution<float> urdY(-25, -5);

	x = urdX(dre);
	stopY = urdY(dre);
}

void Enemy::update(float eTime)
{
	Object::update(eTime);
	shootCoolTime -= eTime;
	
	if (startY < stopY)
		startY += 10 * eTime;
	else {
		x += (traverseDir * 10 * eTime);
		
		if (x < -35)
			traverseDir = 1;
		else if (x > 35)
			traverseDir = -1;
	}

	turn += eTime * 2;

	setPos(x, 0, startY);

	setRotate(0, 0, turn);
}

bool Enemy::canShoot()
{
	if (shootCoolTime < FLT_EPSILON)
		return true;
	return false;
}

void Enemy::resetCoolTime()
{
	shootCoolTime = defaultCoolTime;
}

void Enemy::setDefaultCoolTime(float c)
{
	defaultCoolTime = c;
}

int Enemy::getEnenyType()
{
	return enemyType;
}

void Enemy::setEnemyType(int t)
{
	enemyType = t;
}
