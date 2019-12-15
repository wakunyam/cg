#include "Item.h"

Item::Item()
{
	int dir = rand() % 4;
	switch (dir)
	{
	case 0:
		setVel(10, 10, 0);
		break;
	case 1:
		setVel(10, -10, 0);
		break;
	case 2:
		setVel(-10, -10, 0);
		break;
	case 3:
		setVel(-10, 10, 0);
		break;
	}
}

void Item::update(float eTime)
{
	float x, y, z;
	getPos(&x, &y, &z);
	float vx, vy, vz;
	getVel(&vx, &vy, &vz);
	x += vx * eTime;
	y += vy * eTime;
	z += vz * eTime;
	if (x < -40)
	{
		x = -40;
		setVel(-vx, vy, vz);
	}
	else if (x > 40)
	{
		x = 40;
		setVel(-vx, vy, vz);
	}
	if (y < -50)
	{
		y = -50;
		setVel(vx, -vy, vz);
	}
	else if (y > 50)
	{
		y = 50;
		setVel(vx, -vy, vz);
	}
	setPos(x, y, z);
	remainTime -= eTime;
}

float Item::getRemainTime()
{
	return remainTime;
}

BoundingBox Item::getBoundingBox()
{
	BoundingBox b;

	float x, y, z;
	getPos(&x, &y, &z);

	b.x1 = -x - 2;
	b.z1 = -y - 2;
	b.x2 = -x + 2;
	b.z2 = -y + 2;
	
	//std::cout << "Item" << std::endl;
	//std::cout << b.x1 << " " << b.x2 << ", " << b.z1 << " " << b.z2 << std:: endl;

	return b;
}
