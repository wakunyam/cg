#pragma once
#include "Object.h"
#include "boundingBox.h"

class Boss : public Object
{
	float shootCoolTime = 0.f;
	float x;
	float startY = -60.0f;
	float stopY;
	float traverseDir = -1;
	bool death = false;
	float z = 0;

public:
	Boss();
	~Boss() = default;
	void update(float eTime) override;
	bool canShoot();
	void resetCoolTime();
	void setDeath();
	bool getDeath() const;
	BoundingBox getBoundingBox();
};
