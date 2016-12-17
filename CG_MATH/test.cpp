#include "vector3.h"
#include <iostream>
#include <string>
#include <time.h>
#include <string.h>

#include <GL\glut.h>


#include "Matrix4x4.h"
#include "Quaternion.h"
#include "MathUtil.h"
#include "FPScamera.h"
#include "common.h"


using namespace std;
using namespace CG_MATH;

//ȫ�ֱ���
static bool flag = 1;
FPScamera camera;

// ��ʼ��

void init()
{

}


// �����ƺ���

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

// ���̿��ƺ���

void keyboard(unsigned char key, int x, int y) {
	
	const float step = 0.05f;
	
	// ��дתСд
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
	
	//x ��
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glEnd();

	//y ��
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glEnd();

	//z ��
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();

	glFlush();
	glPopMatrix();
}




void myDisplay(void) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	

	Matrix4x4 p;

	// ����ͶӰ����

	if (flag) {
		//1 ���� identity
		glLoadIdentity();
		gluPerspective(50, 1.0f, 0.01f, 100.0f);

		//glFrustum(-1.0f, 2.0f, -1.5f, 1.9f, 1.0f, 10.0f);

		//printf("ԭ����\n");
	}
	else {
		// 2, ����perspective
		p.setupPerspective(50, 1.0f, 0.01f, 100.0f);
		

		// 3, ����frustum
		//p.setupFrustum(-1.0f, 2.0f, -1.5f, 1.9f, 1.0f, 10.0f);
		setMatrix(p);
		//printf("���Ժ���\n");
	}
	
	flag = !flag;

	// �����������

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	setMatrix(camera.getMatrix());
	
	DrawWorldXYZ();

	//DrawObject(); 
	//Matrix3x4Test();
	//EulerAngleTest();

	QuaternionTest();

	glutSwapBuffers();

}

int main(int argc, char *argv[])
{

	init();

	// init window.

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("test");
	glutDisplayFunc(&myDisplay);
	//glutIdleFunc(&myDisplay);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMainLoop();
	return 0;
}
