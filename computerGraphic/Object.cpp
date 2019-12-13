#include "Object.h"

Object::Object()
{
	hp = 0;
	idx = -1;
	velX = 0.f, velY = 0.f, velZ = 0.f;
	mass = 1.f;
}

Object::~Object()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo_pos);
	glDeleteBuffers(1, &vbo_normal);
}

void Object::initialize(const char* s)
{
	vertexSize = loadObj(s, vertex, normal);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo_pos);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(glm::vec3), &normal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void Object::render(GLuint shaderProgram)
{
	glUseProgram(shaderProgram);

	glm::mat4 model = glm::mat4(1.f);

	model =
		glm::translate(model, glm::vec3(vPos.x * 10, vPos.y * 10, vPos.z * 10))
		* glm::rotate(model, vRotate.z, glm::vec3(0.f, 0.f, 1.f))
		* glm::rotate(model, vRotate.y, glm::vec3(0.f, 1.f, 0.f))
		* glm::rotate(model, vRotate.x, glm::vec3(1.f, 0.f, 0.f))
		* glm::scale(model, glm::vec3(vScale.x * 10, vScale.y * 10, vScale.z * 10));

	unsigned int modelLocation = glGetUniformLocation(shaderProgram, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	unsigned int objectColorLocation = glGetUniformLocation(shaderProgram, "objectColor");
	if (objectColorLocation != -1)
		glUniform3fv(objectColorLocation, 1, glm::value_ptr(objectColor));
	unsigned int alphaLocation = glGetUniformLocation(shaderProgram, "alpha");
	glUniform1f(alphaLocation, alpha);

	glBindVertexArray(vao);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, vertexSize);

	glUseProgram(0);
}

void Object::update(float eTime)
{
	float velSize = sqrtf(velX * velX + velY * velY);
	if (velSize > 0.f) {
		float vX = velX / velSize;
		float vY = velY / velSize;

		// calculate friction size
		float nForce = 9.8f * mass;
		float frictionSize = 0.7f * nForce; // 마찰계수와 중력
		vX = -vX * frictionSize;
		vY = -vY * frictionSize;

		// calculate acc from friction
		float accX = vX / mass;
		float accY = vY / mass;

		// Update velocity
		float newVelX = velX + accX * eTime;
		float newVelY = velY + accY * eTime;
		if (newVelX * velX < 0.f) {
			velX = 0;
		}
		else {
			velX = newVelX;
		}
		if (newVelY * velY < 0.f) {
			velY = 0;
		}
		else {
			velY = newVelY;
		}
	}
	vPos.x = vPos.x + velX * eTime;
	vPos.y = vPos.y + velY * eTime;
}

void Object::setColor(float r, float g, float b)
{
	objectColor = glm::vec3(r, g, b);
}

void Object::translate(float x, float y, float z)
{
	vPos += glm::vec3(x, y, z);
}

void Object::rotate(float x, float y, float z)
{
	vRotate += glm::vec3(x, y, z);
}

void Object::scale(float x, float y, float z)
{
	vScale *= glm::vec3(x, y, z);
}

void Object::setPos(float x, float y, float z)
{
	vPos.x = x;
	vPos.y = y;
	vPos.z = z;
}

void Object::getPos(float* x, float* y, float* z)
{
	*x = vPos.x;
	*y = vPos.y;
	*z = vPos.z;
}

void Object::manageHp(int damage)
{
	hp -= damage;
}

void Object::setIdx(int idx)
{
	this->idx = idx;
}

int Object::getIdx()
{
	return idx;
}

void Object::setType(int type)
{
	this->type = type;
}

int Object::getType()
{
	return type;
}

void Object::setParent(Object* parent)
{
	this->parent = parent;
}

Object* Object::getParent()
{
	return parent;
}

bool Object::isAncestor(Object* obj)
{
	Object* tmp = this;
	while (tmp->getParent() != NULL) 
	{
		if (tmp == obj)
			return true;
		else
			tmp = tmp->getParent();
	}
	return false;
}

void Object::setVel(float x, float y, float z)
{
	velX = x;
	velY = y;
	velZ = z;
}

void Object::getVel(float* x, float* y, float* z)
{
	*x = velX;
	*y = velY;
	*z = velZ;
}

void Object::setHp(int hp)
{
	this->hp = hp;
}

int Object::getHp()
{
	return hp;
}

void Object::addForce(float fx, float fy, float fz, float eTime)
{
	float accX, accY, accZ;
	accX = accY = accZ = 0.f;

	accX = fx / mass;
	accY = fy / mass;
	accZ = fz / mass;

	velX = velX + accX * eTime;
	velY = velY + accY * eTime;
	velZ = velZ + accZ * eTime;
}
