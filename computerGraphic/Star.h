#pragma once
#include "Object.h"

class Star : public Object {
	float x;
	float y;
	float z;

public:
	Star();
	~Star() = default;
	void update(float eTime) override;
};
