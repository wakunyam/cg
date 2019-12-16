#include "BossBody.h"

BossBody::BossBody()
{
	revolution(90.f, 0.f, 0.f);

	x = 0;
	stopY = -20;
}

void BossBody::update(float eTime)
{
	Object::update(eTime);

	

	if (!death) {
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
	else {
		setRotate(120, 0, 0);
		z -= 10 * eTime;
		startY += 5 * eTime;
		setPos(x, z, startY);

		if (z < -30)
			setHp(0);
	}
}

bool BossBody::getDeath() const
{
	return death;
}

void BossBody::setDeath()
{
	death = true;
}

BoundingBox BossBody::getBoundingBox()
{
	BoundingBox b;

	float x, y, z;
	getPos(&x, &y, &z);

	b.x1 = x - 8;
	b.z1 = -z - 8;
	b.x2 = x + 8;
	b.z2 = -z + 8;

	return b;
}
