#pragma once

struct BoundingBox {
	float x1;
	float z1;
	float x2;
	float z2;
};

bool collide(BoundingBox a, BoundingBox b);