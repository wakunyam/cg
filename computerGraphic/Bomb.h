#pragma once
#include "Object.h"

class Bomb : public Object
{
	float remainTime = 3.f;
	float turn = 0;
public:
	Bomb() = default;
	~Bomb() = default;
	void update(float eTime) override;
	float getRemainTime();
};

