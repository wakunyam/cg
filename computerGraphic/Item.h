#pragma once
#include "Object.h"
#include "boundingBox.h"

class Item : public Object
{
	float remainTime = 10.f;
public:
	Item();
	~Item() = default;
	void update(float eTime) override;
	float getRemainTime();
	BoundingBox getBoundingBox();
};

