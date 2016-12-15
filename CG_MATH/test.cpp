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

using namespace std;
using namespace CG_MATH;

//全局变量
static bool flag = 1;
FPScamera camera;

// 初始化

void init()
{

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

		camera.rotate(deltX * -.2f, deltY * -0.2f, 0.0f);
	}

	myDisplay();
}

// 键盘控制函数

void keyboard(unsigned char key, int x, int y) {
	
	printf("key is :%c\n", key);

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

void print(string msg, const vector3 &v)
{
	cout << msg << ' ' << v.x <<' ' << v.y <<' ' << v.z << endl;
}

void testVector3()
{
	{
		cout << endl << "case 1" << endl;
		vector3 a = kZeroVector;
		print("a", a);
	}

	{
		cout << endl << "case 2" << endl;
		vector3 a(1.0f, 1.0f, 1.0f);
		print("a is ", a);
		vector3 b = a;
		print("b is ", b);
		cout << "a==b" << ' ' << (a == b) << endl;
		cout << "a!=b" << ' ' << (a != b) << endl;
		a.zero();
		print("a is ", a);
		print("-b is ", -b);
	}

	{
		cout << endl << "case 3" << endl;
		vector3 a(10.0f, 5.0f, 1.0f);
		vector3 b(1.0f, 3.0f, 10.0f);
		print("a", a);
		print("b", b);
		print("a+b:", a + b);
		print("a-b:", a - b);
		print("a/5:", a / 5);
		print("a*5:", a * 5);
		print("5*a:", 5 * a);
		a += b;
		print("a+=b", a);
		a -= b;
		print("a-=b", a);
		a *= 5;
		print("a*=5", a);
		a /= 5;
		print("a/=5", a);
		cout << endl << "case 4" << endl;
		cout << "a*b " << a*b << endl;
		a.normalize();
		print("a.normalize", a);
		cout << "mag(a) " << vectorMag(a) << endl;
		cout << endl << "case 5" << endl;
		vector3 axb = cross(a, b);
		cout << "a*(axb): " << a*axb << endl;
		cout << "b*(axb): " << b*axb << endl;
		cout << endl << "case 6 " << endl;
		a = vector3(1.0f, 0, 0);
		b = vector3(0, 1.0f, 1.0f);
		cout << "distance of a, b is " << distance(a, b) << endl;
	}


	cout << "performance test" << endl;
	double start, end, cost;
	start = clock();
	for (int i = 0; i < (1 << 25); ++i)
	{
		vector3 a(1.0f, 3.0f, 5.0f);
		a /= 7.0f;
	}
	end = clock();
	cost = end - start;
	cout << cost << endl;

}

void setMatrix(const Matrix4x4& m) {
	float f[16];
	f[0] = m.m11; f[1] = m.m21; f[2] = m.m31; f[3] = m.m41;
	f[4] = m.m12; f[5] = m.m22; f[6] = m.m32; f[7] = m.m42;
	f[8] = m.m13; f[9] = m.m23; f[10] = m.m33; f[11] = m.m43;
	f[12] = m.m14; f[13] = m.m24; f[14] = m.m34; f[15] = m.m44;

	glLoadMatrixf(f);
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

void DrawObject()
{

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -3.0f);

	// 坐标轴
	
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

	glColor3f(0.5f, 0.3f, 0.0f);
	glutSolidTeapot(1.0f);
	
	glPopMatrix();

	glFlush();
}



void myDisplay(void) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	

	Matrix4x4 p;

	// 设置投影矩阵

	if (flag) {
		//1 测试 identity
		glLoadIdentity();
		gluPerspective(50, 1.0f, 0.01f, 100.0f);

		//glFrustum(-1.0f, 2.0f, -1.5f, 1.9f, 1.0f, 10.0f);

		printf("原函数\n");
	}
	else {
		// 2, 测试perspective
		p.setupPerspective(50, 1.0f, 0.01f, 100.0f);
		

		// 3, 测试frustum
		//p.setupFrustum(-1.0f, 2.0f, -1.5f, 1.9f, 1.0f, 10.0f);
		setMatrix(p);
		printf("测试函数\n");
	}
	
	//flag = !flag;

	// 设置相机矩阵

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	setMatrix(camera.getMatrix());
	
	DrawWorldXYZ();

	DrawObject(); 

	glutSwapBuffers();

}

void printQuat(const Quaternion&q)
{
	printf("%f %f %f %f\n", q.w, q.x, q.y, q.z);
}



int main(int argc, char *argv[])
{

	init();

	// init window.

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("test");
	glutDisplayFunc(&myDisplay);
	//glutIdleFunc(&myDisplay);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMainLoop();
	return 0;
}
