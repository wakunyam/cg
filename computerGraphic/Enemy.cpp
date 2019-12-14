#include <random>
#include "Enemy.h"

void Enemy::setEnemyStopPos()
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urdX(-20, 20);
	std::uniform_real_distribution<float> urdY(10, 15);

	startX = urdX(dre);
	stopY = urdY(dre);
}

void Enemy::update(float eTime)
{
	startY -= 10 * eTime;
	turn += eTime * 2;

	if(startY > stopY)
		setPos(startX, startY, 0);

	setRotate(0, turn, 0);
}
