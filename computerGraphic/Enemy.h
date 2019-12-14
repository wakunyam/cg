#pragma once
#include "Object.h"

class Enemy : public Object
{
	float shootCoolTime = 0.f;
public:
	Enemy();
	~Enemy() = default;
	void update(float eTime) override;
	bool canShoot();
	void resetCoolTime();
};

