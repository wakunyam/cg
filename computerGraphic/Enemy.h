#pragma once
#include "Object.h"

class Enemy : public Object
{
	float turn = 0.f;
	float startX;
	float startY = 100.0f;
	float stopY;

public:
	Enemy() = default;
	~Enemy() = default;
	void setEnemyLocation();
	void update(float eTime) override;
};
