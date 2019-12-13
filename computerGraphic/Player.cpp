#include "Player.h"

void Player::update(float eTime)
{
	Object::update(eTime);
	shootCoolTime -= eTime;
	if (evasion)
	{
		turn += 360 * eTime;
		if(turn<360)
			rotate(0.f, 360 * eTime, 0.f);
		else
		{
			turn = 0.f;
			setRotate(-90.f, 0.f, 0.f);
			evasion = false;
		}
	}
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
