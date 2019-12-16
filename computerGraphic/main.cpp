#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "shaderCompiler.h"
#include "camera.h"
#include "loadObj.h"
#include "boundingBox.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Star.h"
#include "Boss.h"
#include "BossBody.h"
#include "Item.h"
#include "Bomb.h"

#define HERO_ID 0
#define ENEMY_SPAWN_TIME 10.f
#define ITEM_SPAWN_TIME 15.f
#define BOSS_SPAWN_TIME 50.f
#define END_DELAY 5.0f

GLvoid drawScene();
GLvoid Reshape(int w, int h);

GLenum drawstyle = GL_FILL;

bool topView = true;

void Timerfounction(int value);
void Keyboard(unsigned char key, int x, int y);
void SpecialKeyDown(int key, int x, int y);
void SpecialKeyUp(int key, int x, int y);

GLuint shaderprogram;
glm::vec3 lightPos = glm::vec3(0.f, 0.f, 500.f);
glm::vec3 lightColor = glm::vec3(1.f, 1.f, 1.f);
unsigned int lightPosLocation, lightColorLocation, viewPosLocation;

glm::vec3 topCameraPos = glm::vec3(0, 0 + 3.0f, 0 + 0.0f);
glm::vec3 backCameraPos = glm::vec3(0, 0, 0 + 3.0f);

objectManager objManager;

int prevTime = 0;

bool keyUp = false;
bool keyLeft = false;
bool keyDown = false;
bool keyRight = false;

float enemySpawnTimer = ENEMY_SPAWN_TIME / 2;
float itemSpawnTimer = ITEM_SPAWN_TIME / 2;

bool bossState = false;
float bossTimer = BOSS_SPAWN_TIME;

bool endState = false;
float endTimer = END_DELAY;

int main(int argc, char** argv) {

	// 윈도우 생성
	glutInit(&argc, argv);                          // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// 디스플레이 모드 설정
	glutInitWindowPosition(300, 0);				    // 윈도우의 위치 지정
	glutInitWindowSize(800, 1000);				    // 윈도우의 크기 지정
	glutCreateWindow("WindowName");                   //윈도우 생성 (윈도우 이름)

	// GLEW 초기화
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized" << std::endl;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	shaderprogram = compileShaders();
	lightColorLocation = glGetUniformLocation(shaderprogram, "lightColor");
	lightPosLocation = glGetUniformLocation(shaderprogram, "lightPos");
	viewPosLocation = glGetUniformLocation(shaderprogram, "viewPos");

	objManager.addObject<Player>(0, 0, 0, 1, 1, 1, 1, 1, 1, PLAYER_TYPE, "plane.obj1");
	auto o = objManager.getObject<Player>(HERO_ID);
	o->setHp(5);
	o->revolution(-90, 0, 0);
	o->setPos(0, 0, -20);
	o->setColor(1, 0, 0);

	objManager.addObject<Bomb>(0, 0, 0, 1, 1, 1, 1, 1, 1, BOMB_TYPE, "boss.obj1");

	for (int i = 0; i < 50; i++) {
		int index = objManager.addObject<Star>(0, 0, 0, 1, 1, 1, 1, 1, 1, STAR_TYPE, "two.obj1");
		auto o = objManager.getObject<Star>(index);
		o->setHp(1);
	}

	objManager.addObject<Item>(0, 0, 0, 1, 1, 1, 1, 1, 1, ITEM_TYPE, "item.obj1");

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyDown);
	glutSpecialUpFunc(SpecialKeyUp);
	glutTimerFunc(33, Timerfounction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

GLvoid drawScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(shaderprogram);

	cameraSetting(shaderprogram, topView);
	glUniform3fv(lightColorLocation, 1, glm::value_ptr(lightColor));
	glUniform3fv(lightPosLocation, 1, glm::value_ptr(lightPos));
	if(topView)
		glUniform3fv(viewPosLocation, 1, glm::value_ptr(topCameraPos));
	else
		glUniform3fv(viewPosLocation, 1, glm::value_ptr(backCameraPos));

	objManager.render(shaderprogram);
	auto o = objManager.getObject<Player>(HERO_ID);
	o->render(shaderprogram);

	glutSwapBuffers();  //  화면에 출력
}

GLvoid Reshape(int w, int h) {  // 다시 그린다
	glViewport(0, 0, w, h);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 's': {
		auto player = objManager.getObject<Player>(HERO_ID);
		if (!player->getDeath()) {
			if (player->canShoot())
			{
				player->resetCoolTime();
				float x, y, z;
				player->getPos(&x, &y, &z);
				if (player->getLevel() >= 3)
				{
					int idx = objManager.addObject<Object>(0, 0, 0, 0.7f, 0.7f, 0.7f, 1, 1, 1, PLAYER_BULLET_TYPE, "bullet.obj1");
					auto o = objManager.getObject<Object>(idx);
					o->setVel(0.f, 50.f, 0.f);
					o->setPos(x + 2.f, y, z + 3.f);
					o->setParent(player);
					o->setHp(10);
					o->revolution(-90, 0, 0);
					o->setColor(1, 1, 0);
				}
				if (player->getLevel() >= 2)
				{
					int idx = objManager.addObject<Object>(0, 0, 0, 0.7f, 0.7f, 0.7f, 1, 1, 1, PLAYER_BULLET_TYPE, "bullet.obj1");
					auto o = objManager.getObject<Object>(idx);
					o->setVel(0.f, 50.f, 0.f);
					o->setPos(x - 2.f, y, z + 3.f);
					o->setParent(player);
					o->setHp(10);
					o->revolution(-90, 0, 0);
					o->setColor(1, 1, 0);
				}
				if (player->getLevel() >= 1)
				{
					int idx = objManager.addObject<Object>(0, 0, 0, 0.7f, 0.7f, 0.7f, 1, 1, 1, PLAYER_BULLET_TYPE, "bullet.obj1");
					auto o = objManager.getObject<Object>(idx);
					o->setVel(0.f, 50.f, 0.f);
					o->setPos(x, y, z + 5.f);
					o->setParent(player);
					o->setHp(10);
					o->revolution(-90, 0, 0);
					o->setColor(1, 1, 0);
				}
			}
		}
		break;
	}
	case 't':
		break;
	case 'y':

		break;
	case 'm':
		if (drawstyle == GL_LINE)
			drawstyle = GL_FILL;
		else
			drawstyle = GL_LINE;
		break;
	case ' ': {
		auto player = objManager.getObject<Player>(HERO_ID);
		player->evade();
		break;
	}
	}
	glutPostRedisplay();
}

void SpecialKeyDown(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		keyUp = true;
	}
	if (key == GLUT_KEY_LEFT)
	{
		keyLeft = true;
	}
	if (key == GLUT_KEY_DOWN)
	{
		keyDown = true;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		keyRight = true;
	}
}

void SpecialKeyUp(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		keyUp = false;
	}
	if (key == GLUT_KEY_LEFT)
	{
		keyLeft = false;
	}
	if (key == GLUT_KEY_DOWN)
	{
		keyDown = false;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		keyRight = false;
	}
	if (key == GLUT_KEY_SHIFT_L)
	{
		topView = (topView + 1) % 2;
		auto o = objManager.getObject<Player>(HERO_ID);
		o->setAlpha(0.1f);
	}
}

void Timerfounction(int value)
{
	int currTime = glutGet(GLUT_ELAPSED_TIME);
	int eTime = currTime - prevTime;
	prevTime = currTime;

	float fx, fy, fz;
	float fAmount = 20.f;
	fx = fy = fz = 0.f;

	auto player = objManager.getObject<Player>(HERO_ID);
	if (!player->getDeath()) {
		if (keyUp)
		{
			fy += 1.f;
		}
		if (keyDown)
		{
			fy -= 1.f;
		}
		if (keyLeft)
		{
			fx -= 1.f;
		}
		if (keyRight)
		{
			fx += 1.f;
		}
	}
	float fSize = sqrtf(fx * fx + fy * fy);
	if (fSize > FLT_EPSILON) {
		fx /= fSize;
		fy /= fSize;

		fx *= fAmount;
		fy *= fAmount;

		auto o = objManager.getObject<Player>(HERO_ID);
		o->addForce(fx, fy, fz, eTime / 1000.f);
	}

	bossTimer -= eTime / 1000.f;
	if (bossTimer > FLT_EPSILON)
	{
		enemySpawnTimer -= eTime / 1000.f;
		if (enemySpawnTimer < FLT_EPSILON) {
			enemySpawnTimer = ENEMY_SPAWN_TIME;
			int enemyType = rand() % 3;
			switch (enemyType)
			{
			case 0: {
				int idx = objManager.addObject<Enemy>(0, 0, 0, 1, 1, 1, 1, 1, 1, ENEMY_TYPE, "enemy.obj1");
				auto e = objManager.getObject<Enemy>(idx);
				e->setEnemyType(0);
				e->setHp(5);
				e->setColor(0, 0.8, 0.3);
				break;
			}
			case 1: {
				int idx = objManager.addObject<Enemy>(0, 0, 0, 1, 1, 1, 1, 1, 1, ENEMY_TYPE, "enemy.obj1");
				auto e = objManager.getObject<Enemy>(idx);
				e->setEnemyType(1);
				e->setHp(5);
				e->setColor(0, 0.8, 0.3);
				break;
			}
			case 2: {
				int idx = objManager.addObject<Enemy>(0, 0, 0, 1, 1, 1, 1, 1, 1, ENEMY_TYPE, "enemy.obj1");
				auto e = objManager.getObject<Enemy>(idx);
				e->setEnemyType(2);
				e->setHp(5);
				e->setDefaultCoolTime(3.f);
				e->setColor(0, 0.8, 0.3);
				break;
			}
			}
		}
	}
	else
	{
		if (!bossState) {
			bossState = true;
			int idx = objManager.addObject<Boss>(0, 0, 0, 5, 5, 5, 1, 1, 1, BOSS_TYPE, "BossArm.obj1");
			auto bossArm = objManager.getObject<Boss>(idx);		
			bossArm->setHp(30);
			bossArm->setColor(0.1, 0.7, 0.4);
			idx = objManager.addObject<BossBody>(0, 0, 0, 5, 5, 5, 1, 1, 1, BOSS_BODY_TYPE, "BossBody.obj1");
			auto bossBody = objManager.getObject<BossBody>(idx);
			bossBody->setHp(10);
			bossBody->setColor(0.1, 0.5, 0.3);
		}
	}

	itemSpawnTimer -= eTime / 1000.f;
	if (itemSpawnTimer < FLT_EPSILON) {
		itemSpawnTimer = ITEM_SPAWN_TIME;
		int idx = objManager.addObject<Item>(0, 0, 0, 1, 1, 1, 1, 1, 1, ITEM_TYPE, "item.obj1");
		auto item = objManager.getObject<Item>(idx);
		item->setColor(1, 0, 0.5);
		item->setHp(1);
	}

	if (endState) {
		endTimer -= eTime / 1000.f;
		if (endTimer < FLT_EPSILON) {
			glutLeaveMainLoop();
		}
	}

	objManager.update(eTime / 1000.f);

	drawScene();
	objManager.doGarbageColletion();

	glutTimerFunc(33, Timerfounction, 1);	
}

