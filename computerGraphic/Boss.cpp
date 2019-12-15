#include "Boss.h"

#define DEFAULT_SHOOT_COOLTIME 1.f

Boss::Boss()
{
	revolution(90.f, 0.f, 0.f);

	x = 0;
	stopY = -20;
}

float Boss::getTurn() const
{
	return turn;
}

void Boss::update(float eTime)
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

	turn += eTime;

	setPos(x, 0, startY);

	setRotate(0, turn, 0);
}



bool Boss::canShoot()
{
	if (shootCoolTime < FLT_EPSILON)
		return true;
	return false;
}

void Boss::resetCoolTime()
{
	shootCoolTime = DEFAULT_SHOOT_COOLTIME;
}
