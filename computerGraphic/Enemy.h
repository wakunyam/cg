#pragma once
#include "Object.h"

class Enemy : public Object
{
	float shootCoolTime = 0.f;
	float defaultCoolTime = 1.5f;
	float turn = 0.f;
	float startX;
	float startY = -60.0f;
	float stopY;
	int enemyType;
public:
	Enemy();
	~Enemy() = default;
	void update(float eTime) override;
	void setEnemyLocation();
	bool canShoot();
	void resetCoolTime();
	void setDefaultCoolTime(float c);
	int getEnenyType();
	void setEnemyType(int t);
};
