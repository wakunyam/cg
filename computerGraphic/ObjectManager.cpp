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
				enemy->resetCoolTime();
				float x, y, z;
				enemy->getPos(&x, &y, &z);
				switch (enemy->getEnenyType())
				{
				case 0: {
					int i = addObject<Object>(0, 0, 0, 1, 1, 1, 1, 1, 1, BULLET_TYPE, "bullet.obj1");
					auto o = getObject<Object>(i);
					o->setVel(0.f, 50.f, 0.f);
					o->setPos(x, y, z + 5.f);
					o->setParent(object);
					o->setHp(10);
					o->revolution(90, 0, 0);
					o->scale(0.7f, 0.7f, 0.7f);
					break;
				}
				case 1: {
					int i = addObject<Object>(0, 0, 0, 1, 1, 1, 1, 1, 1, BULLET_TYPE, "bullet.obj1");
					auto b1 = getObject<Object>(i);
					b1->setVel(0.f, 50.f, 0.f);
					b1->setPos(x, y, z + 5.f);
					b1->setParent(object);
					b1->setHp(10);
					b1->revolution(90, 0, 0);
					b1->scale(0.7f, 0.7f, 0.7f);
					i = addObject<Object>(0, 0, 0, 1, 1, 1, 1, 1, 1, BULLET_TYPE, "bullet.obj1");
					auto b2 = getObject<Object>(i);
					b2->setVel(sqrtf(50.f * 50.f), sqrtf(50.f * 50.f), 0.f);
					b2->setPos(x, y, z + 5.f);
					b2->setParent(object);
					b2->setHp(10);
					b2->revolution(90, 0, 0);
					b2->scale(0.7f, 0.7f, 0.7f);
					b2->rotate(0, 45, 0);
					i = addObject<Object>(0, 0, 0, 1, 1, 1, 1, 1, 1, BULLET_TYPE, "bullet.obj1");
					auto b3 = getObject<Object>(i);
					b3->setVel(-sqrtf(50.f * 50.f), sqrtf(50.f * 50.f), 0.f);
					b3->setPos(x, y, z + 5.f);
					b3->setParent(object);
					b3->setHp(10);
					b3->revolution(90, 0, 0);
					b3->scale(0.7f, 0.7f, 0.7f);
					b3->rotate(0, -45, 0);
					break;
				}
				case 2: {
					int i = addObject<Object>(0, 0, 0, 1, 1, 1, 1, 1, 1, BULLET_TYPE, "bullet.obj1");
					auto o = getObject<Object>(i);
					o->setVel(0.f, 20.f, 0.f);
					o->setPos(x, y, z + 5.f);
					o->setParent(object);
					o->setHp(10);
					o->revolution(90, 0, 0);
					o->scale(2.f, 2.f, 2.f);
					o->setFric(0.f);
					break;
				}
				}
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
	int idx = 0;
	while (it != objects.end())
	{
		if ((*it)->getType() == BULLET_TYPE)
		{
			float x, y, z;
			(*it)->getPos(&x, &y, &z);
			if (z > 60.f)
			{
				(*it) = nullptr;
				objects.erase(it++);
				continue;
			}
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
		if ((*it)->getType() == ITEM_TYPE)
		{
			auto item = getObject<Item>(idx);
			if (item->getRemainTime() < FLT_EPSILON)
			{
				(*it) = nullptr;
				objects.erase(it++);
				continue;
			}
		}
		++idx;
		++it;
	}
}
