#include "Boss.h"

#define DEFAULT_SHOOT_COOLTIME 1.2f

Boss::Boss()
{
	revolution(90.f, 0.f, 0.f);

	x = 0;
	stopY = -20;
}

void Boss::update(float eTime)
{
	Object::update(eTime);

	if (!death) {
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
	else {
		setRotate(120, 0, 0);
		z -= 10 * eTime;
		startY += 5 * eTime;
		setPos(x, z, startY);

		if (z < -30)
			setHp(0);
	}
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

void Boss::setDeath()
{
	death = true;
}

bool Boss::getDeath() const
{
	return death;
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