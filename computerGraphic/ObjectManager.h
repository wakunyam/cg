#pragma once
#include <gl/glew.h>
#include <vector>
#include <list>
#include "object.h"
class objectManager
{
	std::list<Object*> objects;
public:
	template <typename T>
	int addObject(
		float x, float y, float z,
		float sx, float sy, float sz,
		float r, float g, float b,
		int type,
		const char* objFileName) 
	{
		Object* o = new T();
		o->setPos(x, y, z);
		o->scale(sx, sy, sz);
		o->setColor(r, g, b);
		o->setType(type);
		o->initialize(objFileName);
		o->setIdx(objects.size());
		objects.push_back(o);

		return o->getIdx();
	}
	Object* getObject(int idx);
	void update(float eTime);
	void render(GLuint shaderProgram);
	void doGarbageColletion();
};