#include "Player.h"

#define DEFAULT_SHOOT_COOLTIME 0.2f

void Player::update(float eTime)
{
	Object::update(eTime);
	shootCoolTime -= eTime;
	if (evasion)
	{
		if (!death) {
			turn += 180 * eTime;
			if (turn > 90) {
				setRotate(0.f, 0.f, 0.f);
				turn = 0.f;
				evasion = false;
			}
			else
				setRotate(0.f, 0.f, turn);
		}
		else {
			deathTurn += 360 * eTime;
			if (deathTurn > 360) {
				setRotate(0.f, 0.f, 0.f);
				deathTurn = 0.f;
				evasion = false;
				respone();
			}
			else
				setRotate(deathTurn, 0, 0);
		}
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
	level = 1;
}

int Player::getLevel()
{
	return level;
}

bool Player::getEvasion() const
{
	return evasion;
}

void Player::setDeath()
{
	death = true;
	evasion = true;
}

bool Player::getDeath() const
{
	return death;
}

void Player::respone()
{
	death = false;
	evasion = false;
	resetLevel();
}

BoundingBox Player::getBoundingBox()
{
	BoundingBox b;

	float x, y, z;
	getPos(&x, &y, &z);

	b.x1 = x - 4;
	b.z1 = z - 4;
	b.x2 = x + 4;
	b.z2 = z + 4;

	return b;
}