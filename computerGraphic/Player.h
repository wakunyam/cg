#pragma once
#include "Object.h"
#include "boundingBox.h"

class Player : public Object
{
	float shootCoolTime = 0.f;
	bool evasion = false;
	float turn = 0.f;
	int level = 3;
public:
	Player() = default;
	~Player() = default;
	void update(float eTime) override;
	bool canShoot();
	void resetCoolTime();
	void evade();
	void plusLevel();
	void resetLevel();
	int getLevel();
	bool getEvasion() const;
	BoundingBox getBoundingBox();
};

