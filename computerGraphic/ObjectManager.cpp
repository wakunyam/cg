#include "objectManager.h"

void objectManager::update(float eTime)
{
	int idx = 0;
	for (auto& object : objects)
	{
		object->update(eTime);
		if (object->getType() == ENEMY_TYPE)
		{
			auto enemy = getObject<Enemy>(idx);
			if (enemy->canShoot())
			{
				float x, y, z;
				enemy->getPos(&x, &y, &z);
				int i = addObject<Object>(0, 0, 0, 1, 1, 1, 1, 1, 1, BULLET_TYPE, "bullet.obj1");
				auto o = getObject<Object>(i);
				o->setVel(0.f, 50.f, 0.f);
				o->setPos(x, y, z + 5.f);
				o->setParent(object);
				o->setHp(10);
				o->revolution(90, 0, 0);
				o->scale(0.7f, 0.7f, 0.7f);
				enemy->resetCoolTime();
			}
		}
		++idx;
	}
}

void objectManager::render(GLuint shaderProgram)
{
	for (const auto& object : objects)
	{
		object->render(shaderProgram);
	}
}

void objectManager::doGarbageColletion()
{
	auto it = objects.begin();
	while (it != objects.end())
	{
		if ((*it)->getType() == BULLET_TYPE)
		{
			float vx, vy, vz;
			(*it)->getVel(&vx, &vy, &vz);
			float vSize = sqrtf(vx * vx + vy * vy + vz * vz);
			if (vSize < FLT_EPSILON)
			{
				(*it) = nullptr;
				objects.erase(it++);
				continue;
			}
			int hp;
			if ((*it)->getHp() < FLT_EPSILON)
			{
				(*it) = nullptr;
				objects.erase(it++);
				continue;
			}
		}
		++it;
	}
}
