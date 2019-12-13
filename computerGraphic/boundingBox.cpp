#include "boundingBox.h"

bool collide(BoundingBox a, BoundingBox b) {
	if (a.x1 > b.x2) return false;
	if (a.x2 < b.x1) return false;
	if (a.z2 < b.z1) return false;
	if (a.z1 > b.z2) return false;

	return true;
}
