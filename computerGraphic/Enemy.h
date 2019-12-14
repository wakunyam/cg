#pragma once
#include "Object.h"

class Enemy : public Object
{
	float shootCoolTime = 0.f;
	float turn = 0.f;
	float startX;
	float startY = -60.0f;
	float stopY;
public:
	Enemy();
	~Enemy() = default;
	void update(float eTime) override;
	void setEnemyLocation();
	bool canShoot();
	void resetCoolTime();
};
