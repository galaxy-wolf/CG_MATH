#pragma once

#include "Matrix3x4.h"

namespace CG_MATH
{
	class Matrix3x4;

	//----------------------------------------------------------------------------------------
	//Matrix4x4��
	//ʵ��4x4ת������

	class Matrix4x4
	{
	public:

		// ��������

		//�����ֵ
		
		float m11, m12, m13, m14;
		float m21, m22, m23, m24;
		float m31, m32, m33, m34;
		float m41, m42, m43, m44;

		// ��������

		//��Ϊ��λ����

		void identity();

		// ��3x4������
		
		Matrix4x4(Matrix3x4 &a) {

			// ֱ�Ӹ�ֵ

			m11 = a.m11; m12 = a.m12; m13 = a.m13; m14 = a.tx;
			m21 = a.m21; m22 = a.m22; m23 = a.m23; m24 = a.ty;
			m31 = a.m31; m32 = a.m32; m33 = a.m33; m34 = a.tz;
			m41 = 0.0f;  m42 = 0.0f;  m43 = 0.0f;  m44 = 1.0f;
		}

		// Ĭ�Ϲ��캯��
		
		Matrix4x4() = default;

		// ����ͶӰ�任����

		void setupPerspective(float fov, float aspect, float near, float far);
		void setupFrustum(float left, float right, float bottom, float top, float near, float far);

	};

	// �����* �������Ӿ��󣬳˷���˳��������ң���任˳���෴��

	Matrix4x4 operator*(const Matrix4x4 &a, const Matrix4x4 &m);

	// �����*= ���ֺ�c++��׼�﷨һ�¡�

	Matrix4x4 &operator*= (Matrix4x4 &a, const Matrix4x4 &m);

	// ����������

	Matrix4x4 inverse(const Matrix4x4 &m);

}