#pragma once
#include "Object.h"
#include "boundingBox.h"

class Enemy : public Object
{
	float shootCoolTime = 0.f;
	float defaultCoolTime = 1.5f;
	float turn = 0.f;
	float x;
	float startY = -60.0f;
	float stopY;
	float traverseDir = -1;
	int enemyType;
public:
	Enemy();
	~Enemy() = default;
	void update(float eTime) override;
	bool canShoot();
	void resetCoolTime();
	void setDefaultCoolTime(float c);
	int getEnenyType();
	void setEnemyType(int t);
	BoundingBox getBoundingBox();
};
