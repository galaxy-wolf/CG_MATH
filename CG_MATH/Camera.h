#pragma once

#include "vector3.h"
#include "Quaternion.h"
#include "Matrix3x4.h"

using namespace CG_MATH;

class Camera
{
public:

	//��������
	
	vector3 pos;
	Quaternion dir;


	//��������

	// ��ʼ�����λ�ã���������ԭ�㣬����-Z�ᡣ

	Camera() :pos(0.0f, 0.0f, 0.0f), dir(kQuaternionIdentity) {}
	
	//�ƶ�λ��

	void move(float front, float left, float up);

	//ת������

	void rotate(float heading, float pitch, float bank);

	//��ȡ�������

	Matrix3x4 getMatrix();
};

