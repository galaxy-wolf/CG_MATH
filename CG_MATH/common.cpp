#include "common.h"
#include <cstdio>

#include <GL\glut.h>
#include "vector3.h"
#include "EulerAngles.h"
#include "MathUtil.h"
#include "RotationMatrix.h"
#include "Quaternion.h"


void DrawObject()
{

	// ◊¯±Í÷·

	//x ÷·
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glEnd();

	//y ÷·
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glEnd();

	//z ÷·
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();

	glColor3f(0.5f, 0.3f, 0.0f);
	glutSolidTeapot(1.0f);

	glFlush();
}

void DrawAxis(const vector3& p) {

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(.0f, .0f, .0f);
	glVertex3f(p.x, p.y, p.z);
	glEnd();

	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glVertex3f(p.x, p.y, p.z);
	glEnd();
}


void setMatrix(const Matrix4x4& m) {
	float f[16];
	f[0] = m.m11; f[1] = m.m21; f[2] = m.m31; f[3] = m.m41;
	f[4] = m.m12; f[5] = m.m22; f[6] = m.m32; f[7] = m.m42;
	f[8] = m.m13; f[9] = m.m23; f[10] = m.m33; f[11] = m.m43;
	f[12] = m.m14; f[13] = m.m24; f[14] = m.m34; f[15] = m.m44;

	glLoadMatrixf(f);
}
void mulMatrix(const Matrix4x4& m) {

	float f[16];
	f[0] = m.m11; f[1] = m.m21; f[2] = m.m31; f[3] = m.m41;
	f[4] = m.m12; f[5] = m.m22; f[6] = m.m32; f[7] = m.m42;
	f[8] = m.m13; f[9] = m.m23; f[10] = m.m33; f[11] = m.m43;
	f[12] = m.m14; f[13] = m.m24; f[14] = m.m34; f[15] = m.m44;

	glMultMatrixf(f);
}

void Matrix3x4Test() {
	glPushMatrix();

	Matrix3x4 m;
	m.identity();

	mulMatrix(m);

	m.setTranslation(vector3(2.0f, -2.0f, -4.0f));

	mulMatrix(m);

	//
	glPopMatrix();
	glPushMatrix();

	m.setupTanslation(vector3(2.0f, -2.0f, -4.0f));

	mulMatrix(m);
	
	//
	glPopMatrix();
	glPushMatrix();

	m.setupLocalToParent(vector3(2.0f, -2.0f, -4.0f), EulerAngles(kPiOver2, kPiOver2/2, 0));
	//DrawAxis(getPositionFromLocalToParentMatrix(m));

	mulMatrix(m);

	//
	glPopMatrix();
	glPushMatrix();

	RotationMatrix r;
	r.setup(EulerAngles(kPiOver2, kPiOver2 / 2, 0));
	m.setupLocalToParent(vector3(2.0f, -2.0f, -4.0f), r);
	mulMatrix(m);

	//
	glPopMatrix();
	glPushMatrix();


	m.setupLocalToParent(vector3(2.0f, -2.0f, -4.0f), EulerAngles(kPiOver2, kPiOver2 / 2, 0));

	Matrix3x4 m2;

	m2.setupParentToLocal(vector3(2.0f, -2.0f, -4.0f), EulerAngles(kPiOver2, kPiOver2 / 2, 0));
	//vector3 pos = getPositionFromParentToLocalMatrix(m2);
	//printf("%f %f %f\n", pos.x, pos.y, pos.z);
	m2 *= m;
	mulMatrix(m2);

	//
	glPopMatrix();
	glPushMatrix();


	r.setup(EulerAngles(kPiOver2, kPiOver2 / 2, 0));
	m.setupLocalToParent(vector3(2.0f, -2.0f, -4.0f), r);
	mulMatrix(m);

	r.setup(EulerAngles(kPiOver2, kPiOver2 / 2, 0));
	m.setupParentToLocal(vector3(2.0f, -2.0f, -4.0f), r);
	mulMatrix(m);


	//
	glPopMatrix();
	glPushMatrix();

	m.setupRotate(1, kPiOver2/2);
	mulMatrix(m);

	//
	glPopMatrix();
	glPushMatrix();

	m.setupRotate(2, kPiOver2 / 2);
	mulMatrix(m);

	//
	glPopMatrix();
	glPushMatrix();

	m.setupRotate(3, kPiOver2 / 2);
	mulMatrix(m);

	//
	glPopMatrix();
	glPushMatrix();
	vector3 axis = vector3(1.0f, 1.0f, 1.0f);
	DrawAxis(axis);
	axis.normalize();

	m.setupRotate(axis, kPiOver2 / 3);
	mulMatrix(m);

	//
	glPopMatrix();
	glPushMatrix();
	Quaternion q;
	q.setToRotateAboutAxis(axis, kPi);
	m.fromQuaternion(q);
	mulMatrix(m);

	//
	glPopMatrix();
	glPushMatrix();

	m.setupScale(vector3(2.0f, 3.0f, 0.5f));
	mulMatrix(m);

	//
	glPopMatrix();
	glPushMatrix();
	m.setupScaleAlongAxis(axis, 2.0f);
	mulMatrix(m);

	//
	glPopMatrix();
	glPushMatrix();
	m.setupShear(3, 0.5f, 0.6f);
	mulMatrix(m);
	mulMatrix(inverse(m));
	
	//
	glPopMatrix();
	glPushMatrix();
	m.setupProject(axis);
	mulMatrix(m);

	//
	glPopMatrix();
	glPushMatrix();

	//DrawObject();

	m.setupReflect(3, -2.0f);
	mulMatrix(m);

	//
	glPopMatrix();
	glPushMatrix();
	m.setupReflect(axis);
	mulMatrix(m);
	//mulMatrix(inverse(m));

	DrawObject();

	glPopMatrix();
}

void EulerAngleTest() {
	
	EulerAngles e;
	Matrix3x4 m;
	m.setupLocalToParent(vector3(2.0f, -2.0f, -4.0f), EulerAngles(kPi / 2.0f, kPiOver2 / 5.0f, kPiOver2 / 3.0f));

	e.fromObjectToWorldMatrix(m);
	printf("%f %f %f \n", e.heading, e.pitch, e.bank);

	m.setupParentToLocal(vector3(2.0f, -2.0f, -4.0f), EulerAngles(kPi / 2.0f, kPiOver2 / 5.0f, kPiOver2 / 3.0f));
	e.fromWorldToObjectMatrix(m);
	printf("%f %f %f \n", e.heading, e.pitch, e.bank);

	Quaternion h, p, b, q;
	h.setToRotateAboutY(-kPi/2.0f);
	p.setToRotateAboutX(-kPiOver2/5.0f);
	b.setToRotateAboutZ(-kPiOver2 / 3.0f);

	q = h*p*b;

	q.setToRotateInertialToObject(EulerAngles(kPi / 2.0f, kPiOver2 / 5.0f, kPiOver2 / 3.0f));
	
	e.fromInertialToObjectQuaternion(q);
	printf("%f %f %f \n", e.heading, e.pitch, e.bank);

	e.fromObjectToInertialQuternion(conjugate(q));
	printf("%f %f %f \n", e.heading, e.pitch, e.bank);

}

void QuaternionTest() {

	//Quaternion q;
	vector3 v = vector3(1.0f, 1.0f, 1.0f);
	v.normalize();
	//q.setToRotateAboutAxis(v, kPi/4);

	//vector3 axis = q.getRotationAxis();

	//printf("angle : %f, axis : %f %f %f\n", kPi/4, v.x, v.y, v.z);
	//printf("angle : %f, axis : %f %f %f\n", q.getRotationAngle(), axis.x, axis.y, axis.z);

	Quaternion qb, qe;
	qb.setToRotateAboutY(kPiOver2);
	qe.setToRotateAboutY(kPi);

	for (int i = 0; i <= 50; ++i) {

		Quaternion q = slerp(qb, qe, (float)i / 50.0f);
		Quaternion a;

		printf("dot :%f", dotProduct(q, q));

		a.w = 0.0f; a.x = 1.0f; a.y = 0.0f; a.z = 0.0f;
		
		a = conjugate(q) * a*q;

		DrawAxis(vector3(a.x, a.y, a.z));

		printf("%f\n", vectorMag(vector3(a.x, a.y, a.z)));

	}

	//for (int i = 0; i <= 5; ++i) {

	//	Quaternion q = pow(qb, i);
	//	Quaternion a;

	//	q.normalize();
	//	printf("dot :%f", dotProduct(q, q));

	//	a.w = 0.0f; a.x = 1.0f; a.y = 0.0f; a.z = 0.0f;

	//	a = conjugate(q) * a*q;

	//	DrawAxis(vector3(a.x, a.y, a.z));

	//	printf("%f\n", vectorMag(vector3(a.x, a.y, a.z)));

	//}

}
