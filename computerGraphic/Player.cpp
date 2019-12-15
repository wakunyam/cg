#include "Player.h"

#define DEFAULT_SHOOT_COOLTIME 0.2f

void Player::update(float eTime)
{
	Object::update(eTime);
	shootCoolTime -= eTime;
	if (evasion)
	{
		turn += 360 * eTime;
		if (turn > 360) {
			setRotate(0.f, 0.f, 0.f);
			turn = 0.f;
			evasion = false;
		}
		else
			setRotate(0.f, 0.f, turn);
	}
	float x, y, z;
	getPos(&x, &y, &z);
	if (x < -37.f)
		x = -37.f;
	else if (x > 37.f)
		x = 37.f;
	if (z < -47.f)
		z = -47.f;
	else if (z > 47.f)
		z = 47.f;
	setPos(x, y, z);
}

bool Player::canShoot()
{
	if (shootCoolTime < FLT_EPSILON)
		return true;
	return false;
}

void Player::resetCoolTime()
{
	shootCoolTime = DEFAULT_SHOOT_COOLTIME;
}

void Player::evade()
{
	if (!evasion)
	{
		evasion = true;
	}
}

void Player::plusLevel()
{
	++level;
	if (level > 3)
		level = 3;
}

void Player::resetLevel()
{
	level = 0;
}

int Player::getLevel()
{
	return level;
}
