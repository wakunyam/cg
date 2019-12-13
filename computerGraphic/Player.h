#pragma once
#include "Object.h"
#define DEFAULT_SHOOT_COOLTIME 0.2f

class Player : public Object
{
	float shootCoolTime = 0.f;
	bool evasion = false;
	float turn = 0.f;
public:
	Player() = default;
	~Player() = default;
	void update(float eTime) override;
	bool canShoot();
	void resetCoolTime();
	void evade();
};

