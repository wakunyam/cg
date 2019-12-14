#pragma once
#include "Object.h"

class Boss : public Object
{
	float shootCoolTime = 0.f;
	float turn = 0.f;
	float x;
	float startY = -60.0f;
	float stopY;
	float traverseDir = -1;

public:
	Boss();
	~Boss() = default;
	float getTurn() const;
	void update(float eTime) override;
	bool canShoot();
	void resetCoolTime();
};
#pragma once
