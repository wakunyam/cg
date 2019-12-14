#include <random>
#include "Star.h"

void Star::setStarlocation()
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> urd(-40, 40);

	x = urd(dre);
	y = 50;
	z = urd(dre);
}

void Star::update(float eTime)
{
	y -= 5 * eTime;
	setPos(x, y, z);
}
