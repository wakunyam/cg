#pragma once
#include "Object.h"

class Enemy : public Object
{
	float turn = 0.f;
	float startX;
	float startY = 60.0f;
	float stopY;

public:
	Enemy() = default;
	~Enemy() = default;
	void setEnemyStopPos();
	void update(float eTime) override;
};
