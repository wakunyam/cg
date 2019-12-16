#include "Bomb.h"

void Bomb::update(float eTime)
{
	turn += 360 * eTime;
	setRotate(0.f, turn, 0.f);
}

float Bomb::getRemainTime()
{
	return remainTime;
}
