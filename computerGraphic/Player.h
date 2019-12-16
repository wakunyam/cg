#pragma once
#include "Object.h"
#include "boundingBox.h"

class Player : public Object
{
	float shootCoolTime = 0.f;
	bool evasion = false;
	float turn = 0.f;
	int level = 2;
	bool death = false;
	float deathTurn = 0;

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
	void setDeath();
	bool getDeath() const;
	void respone();
	BoundingBox getBoundingBox();
};

