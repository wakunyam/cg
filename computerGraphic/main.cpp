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

#define HERO_ID 0

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

int timeCnt = 70;
int prevTime = 0;

bool keyUp = false;
bool keyLeft = false;
bool keyDown = false;
bool keyRight = false;

int enemySpownTimer = 70;
int starSpownTimer = 30;

int main(int argc, char** argv) {

	// ������ ����
	glutInit(&argc, argv);                          // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// ���÷��� ��� ����
	glutInitWindowPosition(300, 0);				    // �������� ��ġ ����
	glutInitWindowSize(800, 1000);				    // �������� ũ�� ����
	glutCreateWindow("WindowName");                   //������ ���� (������ �̸�)

	// GLEW �ʱ�ȭ
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
	objManager.addObject<Enemy>(0, 0, -10, 1, 1, 1, 1, 1, 1, ENEMY_TYPE, "enemy.obj1");
	auto o = objManager.getObject<Player>(HERO_ID);

	o->revolution(-90, 0, 0);

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
	glutSwapBuffers();  //  ȭ�鿡 ���
}

GLvoid Reshape(int w, int h) {  // �ٽ� �׸���
	glViewport(0, 0, w, h);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 's': {
		auto player = objManager.getObject<Player>(HERO_ID);
		if (player->canShoot())
		{
			player->resetCoolTime();
			int idx = objManager.addObject<Object>(0, 0, 0, 1, 1, 1, 1, 1, 1, BULLET_TYPE, "bullet.obj1");
			auto o = objManager.getObject<Object>(idx);
			float x, y, z;
			player->getPos(&x, &y, &z);
			o->setVel(0.f, 50.f, 0.f);
			o->setPos(x, y, z + 5.f);
			o->setParent(player);
			o->setHp(10);
			o->revolution(-90, 0, 0);
			o->scale(0.7f, 0.7f, 0.7f);
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
	case 'q':
		glutLeaveMainLoop();
		break;
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
	}
}

void Timerfounction(int value)
{
	int currTime = glutGet(GLUT_ELAPSED_TIME);
	int eTime = currTime - prevTime;
	prevTime = currTime;

	float fx, fy, fz;
	float fAmount = 10.f;
	fx = fy = fz = 0.f;

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

	float fSize = sqrtf(fx * fx + fy * fy);
	if (fSize > FLT_EPSILON) {
		fx /= fSize;
		fy /= fSize;

		fx *= fAmount;
		fy *= fAmount;

		auto o = objManager.getObject<Player>(HERO_ID);
		o->addForce(fx, fy, fz, eTime / 1000.f);
	}

	enemySpownTimer++;
	if (enemySpownTimer > 100) {
		enemySpownTimer = 0;
		int idx = objManager.addObject<Enemy>(0, 0, 0, 1, 1, 1, 1, 1, 1, ENEMY_TYPE, "enemy.obj1");
		auto e = objManager.getObject<Enemy>(idx);
		e->setEnemyLocation();
	}

	starSpownTimer++;
	if (starSpownTimer > 50) {
		starSpownTimer = 0;
		int index = objManager.addObject<Star>(0, 0, 0, 1, 1, 1, 1, 1, 1, STAR_TYPE, "sphere.obj1");
		auto o = objManager.getObject<Star>(index);
		o->setStarlocation();
	}


	objManager.update(eTime / 1000.f);

	drawScene();
	objManager.doGarbageColletion();

	glutTimerFunc(33, Timerfounction, 1);	
}

