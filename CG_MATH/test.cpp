#define _CRT_SECURE_NO_WARNINGS
#include "test.h"

#include <GL/glut.h>

#include <cstdio>
#include <assert.h>
#include <iostream>

using namespace CG_MATH;
using namespace DirectX;
using std::cout;
using std::endl;

void redirectOutPut() 
{
	freopen("test-result.txt", "w+", stdout);
}


// helper
std::ostream& operator<<(std::ostream &os, const EulerAngles& e)
{
	os <<"(eulerAngles) "<<e.heading << ", " << e.pitch << ", " << e.bank << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream &os, const Matrix3x4& m)
{
	os << "(matrix4x3) " << std::endl;
	os << m.m11 << ", " << m.m12 << ", " << m.m13 << ", " << m.tx << std::endl;
	os << m.m21 << ", " << m.m22 << ", " << m.m23 << ", " << m.ty << std::endl;
	os << m.m31 << ", " << m.m32 << ", " << m.m33 << ", " << m.tz << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream &os, const Matrix4x4& m)
{
	os << "(matrix4x4) " << std::endl;
	os << m.m11 << ", " << m.m12 << ", " << m.m13 << ", " << m.m14 << std::endl;
	os << m.m21 << ", " << m.m22 << ", " << m.m23 << ", " << m.m24 << std::endl;
	os << m.m31 << ", " << m.m32 << ", " << m.m33 << ", " << m.m34 << std::endl;
	os << m.m41 << ", " << m.m42 << ", " << m.m43 << ", " << m.m44 << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream &os, const Quaternion& q)
{
	os << "(Quaternion)" << std::endl;
	os << q.w << ", " << q.x << ", " << q.y << ", " << q.z << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream &os, const RotationMatrix &rm)
{
	os << "(Rotation Matrix)" << std::endl;
	os << rm.m11 << ", " << rm.m12 << ", " << rm.m13 << std::endl;
	os << rm.m21 << ", " << rm.m22 << ", " << rm.m23 << std::endl;
	os << rm.m31 << ", " << rm.m32 << ", " << rm.m33 << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream &os, const vector3 &v)
{
	os << "(vector)" << v.x << ", " << v.y << ", " << v.z << std::endl;
	return os;
}

bool floatEqual(float a, float b)
{
	return fabsf(a - b) < 1e-5;
}

bool eulerAnglesEqual(const EulerAngles &a, const EulerAngles &b)
{
	return floatEqual(a.heading, b.heading)
		&& floatEqual(a.pitch, b.pitch)
		&& floatEqual(a.bank, b.bank);
}

bool operator==(const Matrix3x4& a, const Matrix3x4 &b)
{
	return
		floatEqual(a.m11, b.m11) && floatEqual(a.m12, b.m12) && floatEqual(a.m13, b.m13) &&
		floatEqual(a.m21, b.m21) && floatEqual(a.m22, b.m22) && floatEqual(a.m23, b.m23) &&
		floatEqual(a.m31, b.m31) && floatEqual(a.m32, b.m32) && floatEqual(a.m33, b.m33) &&
		floatEqual(a.tx, b.tx) && floatEqual(a.ty, b.ty) && floatEqual(a.tz, b.tz);
}

bool vector3Equal(const vector3 &a, const vector3 &b)
{
	return floatEqual(a.x, b.x) &&
		floatEqual(a.y, b.y) &&
		floatEqual(a.z, b.z);
}

bool operator==(const Matrix4x4 &a, const Matrix4x4 &b)
{
	return
		floatEqual(a.m11, b.m11) && floatEqual(a.m12, b.m12) && floatEqual(a.m13, b.m13) && floatEqual(a.m14, b.m14) &&
		floatEqual(a.m21, b.m21) && floatEqual(a.m22, b.m22) && floatEqual(a.m23, b.m23) && floatEqual(a.m24, b.m24) &&
		floatEqual(a.m31, b.m31) && floatEqual(a.m32, b.m32) && floatEqual(a.m33, b.m33) && floatEqual(a.m34, b.m34) &&
		floatEqual(a.m41, b.m41) && floatEqual(a.m42, b.m42) && floatEqual(a.m43, b.m43) && floatEqual(a.m44, b.m44);
}

bool operator==(const Quaternion &q1, const Quaternion &q2)
{
	return floatEqual(q1.w, q2.w) &&
		floatEqual(q1.x, q2.x) &&
		floatEqual(q1.y, q2.y) &&
		floatEqual(q1.z, q2.z);
}

// EulerAngles.cpp
int testEulerAngles()
{
	std::cout << "test EulerAngles: " << std::endl;
	int Error = 0;

	EulerAngles e;
	e.identity();
	cout << e;

	//canonize
	e = EulerAngles(kPi*3, kPi * 2 / 3, kPi*3/2);
	cout << "canonize" << std::endl;
	cout << e;
	e.canonize();
	EulerAngles r = EulerAngles(0.0f, kPi / 3, kPi / 2);
	cout << e<<r;
	assert(eulerAnglesEqual(e, r));

	//万向锁
	e = EulerAngles(kPi, kPi / 2, kPi * 3 / 2);
	cout << "Gimble lock" << endl;
	cout << e;
	e.canonize();
	assert(eulerAnglesEqual(e, EulerAngles(kPi / 2, kPi / 2, 0.0f)));
	cout << e;

	//
	EulerAngles inputE;
	Quaternion q;
	inputE = EulerAngles(kPi / 2.0f, kPiOver2 / 5.0f, kPiOver2 / 3.0f);
	q.setToRotateInertialToObject(inputE);

	e.fromInertialToObjectQuaternion(q);
	std::cout << inputE << e;
	assert(eulerAnglesEqual(inputE, e));

	e.fromObjectToInertialQuternion(conjugate(q));
	std::cout << inputE << e;
	assert(eulerAnglesEqual(inputE, e));

	//
	Matrix3x4 m;
	inputE = EulerAngles(kPi / 2.0f, kPiOver2 / 5.0f, kPiOver2 / 3.0f);
	m.setupLocalToParent(vector3(2.0f, -2.0f, -4.0f), inputE);
	e.fromObjectToWorldMatrix(m);
	std::cout << inputE << e;
	assert(eulerAnglesEqual(inputE, e));

	inputE = EulerAngles(kPi / 2.0f, kPiOver2 / 5.0f, kPiOver2 / 3.0f);
	m.setupParentToLocal(vector3(2.0f, -2.0f, -4.0f), inputE);
	e.fromWorldToObjectMatrix(m);
	std::cout << inputE << e;
	assert(eulerAnglesEqual(inputE, e));

	//
	RotationMatrix rm;
	rm.setup(inputE);
	e.fromRotationMatrix(rm);
	std::cout << e << inputE;
	assert(eulerAnglesEqual(inputE, e));

	std::cout << "test EulerAngles Error num: " <<Error<< std::endl;
	return Error;
}

// FPScamera.cpp
int testFPScamera()
{
	std::cout << "test FPScamera: " << std::endl;
	int Error = 0;
	std::cout << "test FPScamera Error num: " << Error<< std::endl;
	return Error;
}

// MathUtil.cpp
int testMathUtil()
{
	std::cout << "test mathUtil: " << std::endl;
	int Error = 0;
	std::cout << "test mathUtil Error num: " << Error<< std::endl;
	return Error;
}


// Matrix3x4.cpp
int testMatrix4x3()
{
	std::cout << "test Matrix4x3:" << std::endl;
	int Error = 0;

	Matrix3x4 m;
	vector3 pos(1.0f, 2.0f, 3.0f);
	m.identity();
	m.zeroTranslation();
	Matrix3x4 m2;
	m2.identity();
	m2.setTranslation(vector3(1.0f, 2.0f, 3.0f));
	m.setupTranslation(vector3(1.0f, 2.0f, 3.0f));
	assert(m == m2);

	EulerAngles e(kPi * 3 / 2, kPi / 3, -kPi / 2);
	RotationMatrix r;
	r.setup(e);
	m.setupLocalToParent(pos, r);
	m2.setupLocalToParent(pos, e);
	assert(m == m2);
	assert(vector3Equal(getPositionFromLocalToParentMatrix(m), pos));
	assert(vector3Equal(getTranslation(m), pos));

	m.setupParentToLocal(pos, r);
	m2.setupParentToLocal(pos, e);
	assert(m == m2);
	assert(vector3Equal(getPositionFromParentToLocalMatrix(m), pos));

	m.setupRotate(1, kPiOver2 / 2);
	m2.setupLocalToParent(vector3(0.0f, 0.0f, 0.0f),
		EulerAngles(0.0f, kPiOver2 / 2, 0.0f));
	assert(m == m2);

	m.setupRotate(2, kPiOver2 / 2);
	m2.setupLocalToParent(vector3(0.0f, 0.0f, 0.0f),
		EulerAngles(kPiOver2 / 2, 0.0f, 0.0f));
	assert(m == m2);

	m.setupRotate(3, kPiOver2 / 2);
	m2.setupLocalToParent(vector3(0.0f, 0.0f, 0.0f),
		EulerAngles(0.0f, 0.0f, kPiOver2 / 2));
	assert(m == m2);

	vector3 axis = vector3(1.0f, 1.0f, 1.0f);
	axis.normalize();
	m.identity();
	m.setupRotate(axis, kPiOver2 / 3);
	Quaternion q;
	q.setToRotateAboutAxis(axis, kPiOver2/3);
	m2.identity();
	m2.fromQuaternion(q);
	assert(m == m2);

	m.setupScale(vector3(2.0f, 3.0f, 0.5f));

	m.setupScaleAlongAxis(axis, 2.0f);
	m2.setupScaleAlongAxis(axis, 1 / 2.0f);
	assert(inverse(m) == m2);

	m.setupShear(3, 0.5f, 0.6f);

	m.setupProject(axis);

	m.setupReflect(3, -2.0f);

	m.setupReflect(axis);
	m2.identity();
	m *= inverse(m);
	assert(m == m2);

	vector3 a(0.0f, 1.0f, 2.0f);
	a = m*a;
	m = m*m2;

	std::cout << "test Matrix4x3 Error num: " << Error << std::endl;
	return Error;
}

// Matrix4x4.cpp
int testMatrix4x4()
{
	std::cout << "test Matrix4x4:" << std::endl;
	int Error = 0;

	Matrix4x4 m, m2;
	m.identity();
	m.setupPerspectiveFov(90.0f, 2.0f, 1.0f, 100.0f);
	m2.setupFrustum(-2.0f, 2.0f, -1.0f, 1.0f, 1.0f, 100.0f);
	cout << m << m2;
	assert(m == m2);

	m = m*m2;
	m *= m2;

	std::cout << "test Matrix4x4 Error num: " << Error<< std::endl;
	return Error;
}



// Quaternion.cpp
int testQuaternion()
{
	std::cout << "test Quaternion:" << std::endl;
	int Error = 0;

	Quaternion q;
	q.identity();
	float angle = kPiOver2;
	q.setToRotateAboutX(angle);
	assert(floatEqual(q.getRotationAngle(), angle));
	assert(vector3Equal(q.getRotationAxis(), vector3(1.0f, 0.0f, 0.0f)));

	q.setToRotateAboutY(angle);
	assert(floatEqual(q.getRotationAngle(), angle));
	assert(vector3Equal(q.getRotationAxis(), vector3(0.0f, 1.0f, 0.0f)));

	q.setToRotateAboutZ(angle);
	assert(floatEqual(q.getRotationAngle(), angle));
	assert(vector3Equal(q.getRotationAxis(), vector3(0.0f, 0.0f, 1.0f)));

	vector3 axis(1.0f, 2.0f, 3.0f);
	axis.normalize();
	q.setToRotateAboutAxis(axis, angle);
	assert(floatEqual(q.getRotationAngle(), angle));
	assert(vector3Equal(q.getRotationAxis(), axis));

	Quaternion q1, q2;
	EulerAngles e(kPi, kPiOver2 / 3, kPi);
	q1.setToRotateObjectToInertial(e);
	q2.setToRotateInertialToObject(e);
	assert(q1 == conjugate(q2));

	q1 *= q2;
	q1 = q1*q2;
	q1.normalize();

	dotProduct(q1, q2);

	// slerp in demo;

	std::cout << "quaternion pow:" << std::endl;
	std::cout <<q1<< pow(q1, 0.5);

	std::cout << "test Quaternion error num: " << Error << std::endl;
	return Error;
}



// RotationMatrix.cpp
bool operator==(const RotationMatrix &a, const RotationMatrix &b)
{
	return
		floatEqual(a.m11 ,b.m11) && floatEqual(a.m12 ,b.m12) && floatEqual(a.m13 ,b.m13) &&
		floatEqual(a.m21 ,b.m21) && floatEqual(a.m22 ,b.m22) && floatEqual(a.m23 ,b.m23) &&
		floatEqual(a.m31 ,b.m31) && floatEqual(a.m32 ,b.m32) && floatEqual(a.m33 ,b.m33);
}

int testRotationMatrix()
{
	std::cout << "test RotationMatrix:" << std::endl;
	int Error = 0;

	RotationMatrix r, r1, r2;
	Quaternion q1, q2;

	q1.setToRotateObjectToInertial(EulerAngles(kPiOver2 / 2, kPiOver2 / 3, kPiOver2));
	r1.fromObjectToInertialQuaternion(q1);
	q2.setToRotateInertialToObject(EulerAngles(kPiOver2 / 2, kPiOver2 / 3, kPiOver2));
	r2.fromInertialToObjectQuaternion(q2);
	assert(r1 == r2);
	
	r.identity();
	r.setup(EulerAngles(kPiOver2/2, kPiOver2/3, kPiOver2));

	vector3 v(1.0f, 2.0f, 3.0f);
	v = r.inertialToObject(v);
	v = r.objectToInertial(v);
	assert(vector3Equal(v, vector3(1.0f, 2.0f, 3.0f)));

	std::cout << "test RoationMatrix error num: " << Error << std::endl;
	return Error;
}

// Vector3.cpp
int testVector3()
{
	std::cout << "test vector3:" << std::endl;
	int Error = 0;

	{
		vector3 a(1.0f, 1.0f, 1.0f);
		vector3 b = a;
		assert(a == b);
		a.zero();
		b = -b;
	}

	{
		vector3 p(10.0f, 5.0f, 1.0f);
		vector3 a = p;
		vector3 b(1.0f, 3.0f, 10.0f);
		a = a + b;
		a = a - b;
		assert(vector3Equal(a, p));
		a = a / 5;
		a = a * 5;
		assert(vector3Equal(a, p));
		a = a / 5;
		a = 5 * a;
		assert(vector3Equal(a, p));
		a += b;
		a -= b;
		assert(vector3Equal(a, p));
		a *= 5;
		a /= 5;
		assert(vector3Equal(a, p));
		float r = 35.0f;
		assert(floatEqual(a*b, r));
		float mag = vectorMag(a);
		a.normalize();
		a *= mag;
		assert(vector3Equal(a, p));

		vector3 axb = cross(a, b);
		assert(vector3Equal(axb, vector3(47.0f, -99.0f, 25.0f)));
		a = vector3(1.0f, 0, 0);
		b = vector3(0, 1.0f, 1.0f);
		assert(floatEqual(distance(a, b), sqrtf(3.0f)));
	}

	std::cout << "test vector3 error num: " << Error << std::endl;
	return Error;
}

int testAllFile()
{
	std::cout << "test all file:" << std::endl;
	int Error = 0;
	Error += testEulerAngles();
	Error += testFPScamera();
	Error += testMathUtil();
	Error += testMatrix4x3();
	Error += testMatrix4x4();
	Error += testQuaternion();
	Error += testRotationMatrix();
	Error += testVector3();

	if (Error == 0)
		std::cout << "no Error in CG_MATH." << std::endl;
	else
		std::cout << "test all file error num: " << Error << std::endl;

	return Error;
}

//int main()
//{
//	redirectOutPut();
//	testAllFile();
//}

//场景中的测试项
//
void DrawObject()
{
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

	glFlush();
}

void DrawAxis(const vector3& p, float r, float g, float b) 
{

	glColor3f(r, g, b);
	glBegin(GL_LINES);
	glVertex3f(.0f, .0f, .0f);
	glVertex3f(p.x, p.y, p.z);
	glEnd();

	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glVertex3f(p.x, p.y, p.z);
	glEnd();
}


void toColomnMajorArray(float *const f, const Matrix4x4& m)
{
	f[0] = m.m11; f[1] = m.m21; f[2] = m.m31; f[3] = m.m41;
	f[4] = m.m12; f[5] = m.m22; f[6] = m.m32; f[7] = m.m42;
	f[8] = m.m13; f[9] = m.m23; f[10] = m.m33; f[11] = m.m43;
	f[12] = m.m14; f[13] = m.m24; f[14] = m.m34; f[15] = m.m44;
}

void toRowMajorArray(float *const f, const Matrix4x4 &m)
{
	f[0] = m.m11; f[1] = m.m12; f[2] = m.m13; f[3] = m.m14; 
	f[4] = m.m21; f[5] = m.m22; f[6] = m.m23; f[7] = m.m24; 
	f[8] = m.m31; f[9] = m.m32; f[10] = m.m33; f[11] = m.m34; 
	f[12] = m.m41; f[13] = m.m42; f[14] = m.m43; f[15] = m.m44; 
}
void setRowMatrix(const Matrix4x4 &m)
{
	float f[16];
	//toColomnMajorArray(f, m);
	toRowMajorArray(f, m);
	glLoadMatrixf(f);
}

void setMatrix(const Matrix4x4& m) 
{
	float f[16];
	toColomnMajorArray(f, m);
	//toRowMajorArray(f, m);
	glLoadMatrixf(f);
}
void mulMatrix(const Matrix4x4& m) 
{
	float f[16];
	toColomnMajorArray(f, m);
	//toRowMajorArray(f, m);

	glMultMatrixf(f);
}

void QuaternionSlerpTest()
{
	//Quaternion q;
	vector3 v = vector3(1.0f, 1.0f, 1.0f);
	v.normalize();
	Quaternion qb, qe;
	vector3 startColor = { 1.0f, 1.0f, 0.0f };
	vector3 endColor = { 0.0f, 1.0f, 1.0f };
	qb.setToRotateAboutY(kPiOver2);
	qe.setToRotateAboutZ(kPi);

	int N = 20;
	for (int i = 0; i <= N; ++i) {

		float t = (float)i / N;
		Quaternion q = slerp(qb, qe, t);
		Quaternion a;

		a.w = 0.0f; a.x = 1.0f; a.y = 0.0f; a.z = 0.0f;
		a = conjugate(q) * a*q;

		vector3 color = startColor + (endColor - startColor)*t;

		DrawAxis(vector3(a.x, a.y, a.z), color.x, color.y, color.z);

	}

}

void QuaternionPowTest()
{
	Quaternion qb, qe;
	vector3 axis(1.0f, 1.0f, 1.0f);
	axis.normalize();
	qb.setToRotateAboutAxis(axis, kPiOver2);

	vector3 startColor = { 1.0f, 1.0f, 0.0f };
	vector3 endColor = { 0.0f, 1.0f, 1.0f };

	float max = 2.0f;
	for (float t = 0.0f; t< max+1e-5; t+=0.2f)
	{
		Quaternion q = pow(qb, t);
		Quaternion a;

		a.w = 0.0f; a.x = 1.0f; a.y = 0.0f; a.z = 0.0f;
		a = conjugate(q) * a*q;

		vector3 color = startColor + (endColor - startColor)*(t/max);

		DrawAxis(vector3(a.x, a.y, a.z), color.x, color.y, color.z);
	}

}