#pragma once
#include "Object.h"

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

