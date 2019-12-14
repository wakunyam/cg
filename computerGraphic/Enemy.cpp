#include <random>
#include "Enemy.h"

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
	if (startY > stopY)
		startY -= 10 * eTime;
	turn += eTime * 2;

	setPos(startX, startY, 0);

	setRotate(0, turn, 0);
}
