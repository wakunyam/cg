#include "Boss.h"

#define DEFAULT_SHOOT_COOLTIME 1.f

Boss::Boss()
{
	revolution(90.f, 0.f, 0.f);

	x = 0;
	stopY = -20;
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

	setPos(x, 0, startY);
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

BoundingBox Boss::getBoundingBox()
{
	BoundingBox b;

	float x, y, z;
	getPos(&x, &y, &z);

	b.x1 = x - 15;
	b.z1 = -z - 10;
	b.x2 = x + 15;
	b.z2 = -z + 10;

	return b;
}