#pragma once
#include "Object.h"
#include "boundingBox.h"

class BossBody : public Object
{
	float turn = 0.f;
	float x;
	float startY = -60.0f;
	float stopY;
	float traverseDir = -1;
	bool death = false;
	float z = 0;

public:
	BossBody();
	~BossBody() = default;
	void update(float eTime) override;
	bool getDeath() const;
	void setDeath();
	BoundingBox getBoundingBox();
};
