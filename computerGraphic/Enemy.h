#pragma once
#include "Object.h"

class Enemy : public Object
{
	float shootCoolTime = 0.f;
	float turn = 0.f;
	float x;
	float startY = -60.0f;
	float stopY;
	float traverseDir = -1;

public:
	Enemy();
	~Enemy() = default;
	void update(float eTime) override;
	bool canShoot();
	void resetCoolTime();
};
