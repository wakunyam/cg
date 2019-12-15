#include "objectManager.h"
#include "boundingBox.h"

#define HERO_ID 0

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
					o->setColor(0, 1, 1);
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
					b1->setColor(0, 1, 1);
					i = addObject<Object>(0, 0, 0, 1, 1, 1, 1, 1, 1, BULLET_TYPE, "bullet.obj1");
					auto b2 = getObject<Object>(i);
					b2->setVel(sqrtf(50.f * 50.f), sqrtf(50.f * 50.f), 0.f);
					b2->setPos(x, y, z + 5.f);
					b2->setParent(object);
					b2->setHp(10);
					b2->revolution(90, 0, 0);
					b2->scale(0.7f, 0.7f, 0.7f);
					b2->rotate(0, 45, 0);
					b2->setColor(0, 1, 1);
					i = addObject<Object>(0, 0, 0, 1, 1, 1, 1, 1, 1, BULLET_TYPE, "bullet.obj1");
					auto b3 = getObject<Object>(i);
					b3->setVel(-sqrtf(50.f * 50.f), sqrtf(50.f * 50.f), 0.f);
					b3->setPos(x, y, z + 5.f);
					b3->setParent(object);
					b3->setHp(10);
					b3->revolution(90, 0, 0);
					b3->scale(0.7f, 0.7f, 0.7f);
					b3->rotate(0, -45, 0);
					b3->setColor(0, 1, 1);
					break;
				}
				case 2: {
					int i = addObject<Object>(0, 0, 0, 1, 1, 1, 1, 1, 1, BULLET_TYPE, "bullet.obj1");
					auto o = getObject<Object>(i);
					o->setVel(0.f, 20.f, 0.f);
					o->setPos(x, y, z + 5.f);
					o->setParent(object);
					o->setHp(20);
					o->revolution(90, 0, 0);
					o->scale(2.f, 2.f, 2.f);
					o->setFric(0.f);
					o->setColor(0, 1, 1);
					break;
				}
				}
			}
			int sub_idx = 0;
			for (auto& sub_object : objects) {
				if (sub_object->getType() == PLAYER_BULLET_TYPE) {
					auto playerBullet = getObject<Object>(sub_idx);
					if (playerBullet->getHp() > 0) {
						float x_bullet, y_bullet, z_bullet;

						playerBullet->getPos(&x_bullet, &y_bullet, &z_bullet);

						BoundingBox bb;
						bb.x1 = x_bullet - 1;
						bb.z1 = z_bullet - 2;
						bb.x2 = x_bullet + 1;
						bb.z2 = z_bullet + 2;

						if (collide(bb, enemy->getBoundingBox())) {
							enemy->manageHp(1);
							playerBullet->setHp(0);
							if (enemy->getHp() <= 0)
								break;
						}
					}
				}
				else if (sub_object->getType() == PLAYER_TYPE) {
					auto player = getObject<Player>(HERO_ID);
					float x_player, y_player, z_player;

					player->getPos(&x_player, &y_player, &z_player);

					BoundingBox bb;
					bb.x1 = x_player - 5;
					bb.z1 = z_player - 5;
					bb.x2 = x_player + 5;
					bb.z2 = z_player + 5;

					if (collide(bb, enemy->getBoundingBox())) {
						enemy->setHp(0);
						player->resetLevel();;
						break;
					}
				}
				++sub_idx;
			}
		}
		if (object->getType() == BOSS_TYPE)
		{
			auto boss = getObject<Boss>(idx);
			if (boss->canShoot())
			{
				for (int way = 0; way < 360; way += 45) {
					float x, y, z;
					boss->getPos(&x, &y, &z);
					int i = addObject<Object>(0, 0, 0, 1, 1, 1, 1, 1, 1, BULLET_TYPE, "bullet.obj1");
					auto o = getObject<Object>(i);
					o->setVel(0.f, 30.f, 0.f);
					o->setPos(0, 0, 0);
					o->setParent(object);
					o->setHp(10);
					o->revolution(90, 0, way);
					o->scale(0.7f, 0.7f, 0.7f);
					o->setColor(0, 1, 1);
				}
				boss->resetCoolTime();
			}
			int sub_idx = 0;
			for (auto& sub_object : objects) {
				if (sub_object->getType() == PLAYER_BULLET_TYPE) {
					auto playerBullet = getObject<Object>(sub_idx);
					if (playerBullet->getHp() > 0) {
						float x_bullet, y_bullet, z_bullet;

						playerBullet->getPos(&x_bullet, &y_bullet, &z_bullet);

						BoundingBox bb;
						bb.x1 = x_bullet - 1;
						bb.z1 = z_bullet - 2;
						bb.x2 = x_bullet + 1;
						bb.z2 = z_bullet + 2;

						if (collide(bb, boss->getBoundingBox())) {
							boss->manageHp(1);
							playerBullet->setHp(0);
							if (boss->getHp() <= 0)
								break;
						}
					}
				}
				else if (sub_object->getType() == PLAYER_TYPE) {
					auto player = getObject<Player>(HERO_ID);
					float x_player, y_player, z_player;

					player->getPos(&x_player, &y_player, &z_player);

					BoundingBox bb;
					bb.x1 = x_player - 5;
					bb.z1 = z_player - 5;
					bb.x2 = x_player + 5;
					bb.z2 = z_player + 5;

					if (collide(bb, boss->getBoundingBox())) {
						player->resetLevel();
						break;
					}
				}
				++sub_idx;
			}
		}
		if (object->getType() == PLAYER_TYPE)
		{
			auto player = getObject<Player>(HERO_ID);
			int sub_idx = 0;
			for (auto& sub_object : objects) {
				if (sub_object->getType() == BULLET_TYPE) {
					if (!sub_object->isAncestor(player)) {
						auto bullet = getObject<Object>(sub_idx);
						if (bullet->getHp() > 0) {
							float x_bullet, y_bullet, z_bullet;
							bullet->getPos(&x_bullet, &y_bullet, &z_bullet);
							
							BoundingBox bb;

							if (bullet->getHp() > 10) {
								bb.x1 = x_bullet - 2;
								bb.z1 = -z_bullet - 3;
								bb.x2 = x_bullet + 2;
								bb.z2 = -z_bullet + 3;
							}
							else {
								bb.x1 = x_bullet - 1;
								bb.z1 = -z_bullet - 2;
								bb.x2 = x_bullet + 1;
								bb.z2 = -z_bullet + 2;
							}

							if (collide(bb, player->getBoundingBox())) {
								if (bullet->getHp() > 10)
									player->manageHp(2);
								else
									player->manageHp(1);
								bullet->setHp(0);
								if (player->getHp() <= 0) {
									player->resetLevel();
									player->setHp(5);
								}
							}
						}
					}
				}
				++sub_idx;
			}
		}
		if (object->getType() == ITEM_TYPE) {
			auto item = getObject<Item>(idx);
			auto player = getObject<Player>(HERO_ID);

			if (collide(item->getBoundingBox(), player->getBoundingBox())) {
				item->setHp(0);
				player->plusLevel();
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
		if ((*it)->getHp() <= 0)
		{
			(*it) = nullptr;
			objects.erase(it++);
			continue;
		}
		if ((*it)->getType() == BULLET_TYPE || (*it)->getType() == PLAYER_BULLET_TYPE)
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
