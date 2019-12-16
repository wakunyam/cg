#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <gl/glew.h>
#include <vector>
#include "loadObj.h"

enum type {
	PLAYER_TYPE = 0,
	BULLET_TYPE,
	ENEMY_TYPE,
	BOSS_TYPE,
	BOSS_BODY_TYPE,
	STAR_TYPE,
	ITEM_TYPE,
	PLAYER_BULLET_TYPE,
};

class Object
{
	glm::vec3 vPos = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 vRotate = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 vScale = glm::vec3(1.f, 1.f, 1.f);
	glm::vec3 vRev = glm::vec3(0.f, 0.f, 0.f);

	unsigned int vertexSize;
	std::vector<glm::vec3> vertex;
	std::vector<glm::vec3> normal;

	glm::vec3 objectColor = glm::vec3(0.f, 0.f, 0.f);
	float alpha = 1.f;

	GLuint vao, vbo_pos, vbo_normal;

	int hp;
	int idx;
	int type;
	float velX, velY, velZ;
	float mass;
	float fric = 0.7f;
	Object* parent = NULL;
public:
	Object();
	~Object();
	void initialize(const char* s);
	void render(GLuint shaderProgram);
	virtual void update(float eTime);
	void setColor(float r, float g, float b);
	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);
	void revolution(float x, float y, float z);
	void setPos(float x, float y, float z);
	void getPos(float* x, float* y, float* z);
	void setRotate(float x, float y, float z);
	void setIdx(int idx);
	int getIdx();
	void setType(int type);
	int getType();
	void setParent(Object* parent);
	Object* getParent();
	bool isAncestor(Object* obj);
	void setVel(float x, float y, float z);
	void getVel(float* x, float* y, float* z);
	void setFric(float fric);
	void setHp(int hp);
	int getHp();
	void manageHp(int damage);
	void addForce(float fx, float fy, float fz, float eTime);
};

