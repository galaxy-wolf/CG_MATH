//////////////////////////////////////////
// 简单场景中 测试
// 1, 首先会调用test.cpp 中的测试项。
// 2, FPScamera
// 3, Matrix4x4 中的setupPerspectiveFOV 与glPerspective，
//		setupFrustum 与 glFrustum 的对比。
// 4, Quaternion slerp
// 5, Quaternion pow
//////////////////////////////////////////


#include <iostream>
#include <string>
#include <time.h>
#include <string.h>

#include <GL\glut.h>
#include "MathUtil.h"
#include "vector3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include "FPScamera.h"
#include "test.h"


using namespace std;
using namespace CG_MATH;

//全局变量
static bool flag = 1;
FPScamera camera;

// 初始化

void init()
{
	camera.pos = vector3(0.0f, 0.0f, 10.0f);
}


// 鼠标控制函数

static int lastX;
static int lastY;
static bool EnableMouseMove = false;


void myDisplay();
void mouse(int button, int state, int x, int y) {

	if (state == GLUT_DOWN) {
		lastX = x;
		lastY = y;
		EnableMouseMove = true;
	}
	else {
		EnableMouseMove = false;
	}
}

void motion(int x, int y) {

	if (EnableMouseMove) {
		int deltX = x - lastX;
		int deltY = y - lastY;

		lastX = x;
		lastY = y;

		camera.rotate2D(deltX * -.2f, deltY * -0.2f);
	}

	myDisplay();
}

// 键盘控制函数

void keyboard(unsigned char key, int x, int y) {

	const float step = 0.05f;

	// 大写转小写
	if ('A' <= key && key <= 'Z')
		key += 'a' - 'A';

	switch (key)
	{
	case 'w':
		camera.move(step, 0, 0);
		break;

	case 's':
		camera.move(-step, 0, 0);
		break;

	case 'a':
		camera.move(0, step, 0);
		break;

	case 'd':
		camera.move(0, -step, 0);
		break;

	case 'q':
		camera.move(0, 0, step);
		break;

	case 'e':
		camera.move(0, 0, -step);
		break;


	default:
		break;
	}

	myDisplay();
}




void DrawWorldXYZ()
{

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glScalef(10.0f, 10.0f, 10.0f);

	//x 轴
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glEnd();

	//y 轴
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glEnd();

	//z 轴
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();

	glFlush();
	glPopMatrix();
}

void readProj()
{
	float m[16];
	glGetFloatv(GL_PROJECTION_MATRIX, m);

	std::cout << "project matrix:" << std::endl;
	std::cout << m[0] << ", " << m[4] << ", " << m[8] << ", " << m[12] << std::endl;
	std::cout << m[1] << ", " << m[5] << ", " << m[9] << ", " << m[13] << std::endl;
	std::cout << m[2] << ", " << m[6] << ", " << m[10] << ", " << m[14] << std::endl;
	std::cout << m[3] << ", " << m[7] << ", " << m[11] << ", " << m[15] <<std::endl;
}


void myDisplay(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);

	Matrix4x4 p;

	// 设置投影矩阵
	if (flag) {
		glLoadIdentity();
		gluPerspective(50, 1.0f, 0.01f, 100.0f);

		//glFrustum(-1.0f, 2.0f, -1.5f, 1.9f, 1.0f, 10.0f);
	}
	else {
		// @@ 测试perspective
		p.setupPerspectiveFov(50, 1.0f, 0.01f, 100.0f);

		// @@ 测试frustum
		//p.setupFrustum(-1.0f, 2.0f, -1.5f, 1.9f, 1.0f, 10.0f);
		setMatrix(p);
	}

	//if (flag)
	//	std::cout << "glFrustum" << std::endl;
	//else
	//	std::cout << "my perspective" << std::endl;
	//readProj();

	flag = !flag;

	// 设置相机矩阵

	glMatrixMode(GL_MODELVIEW);
	setMatrix(Matrix4x4(camera.getMatrix()));

	DrawWorldXYZ();

	glPushMatrix();
	Matrix3x4 m;
	m.setupTranslation(vector3(-4.0f, 0.0f, 0.0f));
	mulMatrix(Matrix4x4(m));
	DrawObject(); 
	glPopMatrix();

	// @@ test quaternion pow
	glPushMatrix();
	m;
	m.setupTranslation(vector3(4.0f, 0.0f, 0.0f));
	mulMatrix(Matrix4x4(m));
	QuaternionPowTest();
	glPopMatrix();

	// @@ test quaternion slerp
	QuaternionSlerpTest();


	glutSwapBuffers();

}

int main(int argc, char *argv[])
{
	// @@ test.cpp 中的测试项
	redirectOutPut();
	testAllFile();


	init();

	// init window.

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("CG_MATH Test");
	glutDisplayFunc(&myDisplay);
	//glutIdleFunc(&myDisplay);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMainLoop();
	return 0;
}
