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
