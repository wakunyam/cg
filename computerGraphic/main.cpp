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

int main(int argc, char** argv) {

	// 윈도우 생성
	glutInit(&argc, argv);                          // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// 디스플레이 모드 설정
	glutInitWindowPosition(300, 100);				// 윈도우의 위치 지정
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

	objManager.addObject<Object>(0, 0, 0, 1, 1, 1, 1, 1, 1, PLAYER_TYPE, "boss.obj1");
	auto o = objManager.getObject(HERO_ID);
	o->rotate(-90, 0, 0);
	
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

	glutSwapBuffers();  //  화면에 출력
}

GLvoid Reshape(int w, int h) {  // 다시 그린다
	glViewport(0, 0, w, h);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 's': {
		int idx = objManager.addObject<Object>(0, 0, 0, 1, 1, 1, 1, 1, 1, BULLET_TYPE, "plane.obj1");
		auto o = objManager.getObject(idx);
		auto player = objManager.getObject(HERO_ID);
		o->setVel(0.f, 10.f, 0.f);
		o->setParent(player);
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
	case ' ':
		break;
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

		auto o = objManager.getObject(HERO_ID);
		o->addForce(fx, fy, fz, eTime / 1000.f);
	}

	objManager.update(eTime / 1000.f);

	drawScene();

	objManager.doGarbageColletion();

	glutTimerFunc(33, Timerfounction, 1);	
}

