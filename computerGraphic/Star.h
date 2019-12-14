#pragma once
#include "Object.h"

class Star : public Object {
	float x;
	float y;
	float z;

public:
	void setStarlocation();
	void update(float eTime) override;
};