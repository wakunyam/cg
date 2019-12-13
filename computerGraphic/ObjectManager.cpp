#include "objectManager.h"

Object* objectManager::getObject(int idx)
{
	auto it = objects.begin();
	for (int i = 0; i < idx; i++)
	{
		it++;
	}
	return *it;
}

void objectManager::update(float eTime)
{
	for (auto& object : objects)
	{
		object->update(eTime);
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
				it = objects.erase(it);
				continue;
			}
			int hp;
			if ((*it)->getHp() < FLT_EPSILON)
			{
				(*it) = nullptr;
				it = objects.erase(it);
				continue;
			}
		}
		++it;
	}
}
