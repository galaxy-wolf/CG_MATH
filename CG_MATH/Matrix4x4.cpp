#include <assert.h>
#include <math.h>

#include "MathUtil.h"
#include "Matrix4x4.h"
#include "Matrix3x4.h"

namespace CG_MATH
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//����������ʾͶӰ�任����
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Matrix4x4 ���Ա
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//��Ϊ��λ����

	void Matrix4x4::identity() {
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f; m14 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f; m24 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f; m34 = 0.0f;
		m41 = 0.0f; m42 = 0.0f; m43 = 0.0f; m44 = 1.0f;
	}

	Matrix4x4::Matrix4x4(const Matrix3x4 &a)
	{
		// ֱ�Ӹ�ֵ

		m11 = a.m11; m12 = a.m12; m13 = a.m13; m14 = a.tx;
		m21 = a.m21; m22 = a.m22; m23 = a.m23; m24 = a.ty;
		m31 = a.m31; m32 = a.m32; m33 = a.m33; m34 = a.tz;
		m41 = 0.0f;  m42 = 0.0f;  m43 = 0.0f;  m44 = 1.0f;
	}

	//����ͶӰ����
	void Matrix4x4::setupPerspectiveFov(float fov, float aspect, float near, float far) 
	{

		assert(aspect != 0.0f);
		assert(near > 0.0f);
		assert(far > 0.0f);

		// ת���ɻ���
		fov *= kPi / 180.0f;

		assert(0.0f < fov && fov < kPi);
		assert(aspect != 0.0f);

		//���㹫��ֵ��

		float f = 1.0f / (tanf(fov *0.5f));
		float nf = near - far;

		assert(fabs(nf) > 0.00001);

		m11 = f / aspect;
		m12 = 0.0f;
		m13 = 0.0f;
		m14 = 0.0f;

		m21 = 0.0f;
		m22 = f;
		m23 = 0.0f;
		m24 = 0.0f;

	// OpenGL ʹ����������ϵ�� ��ͶӰ���еĵ�ֲ���Z��ĸ�����
	// �ر�ע�⺯�������е�near, far ����ֵ, zֵ�ı任Ӧ���Ǵ�[-far, -near] ��[1, -1] �����Ա任
	// �Ƶ����̣�
	// z' = (m33z+m34)/w , w = -z
	// ������� (z'=1, z= -far) �� (z'=-1, z= -near) ������ 
	// �Ϳ������m33, m34
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = (far + near) / nf;
		m34 = 2 * far*near / nf;

		m41 = 0.0f;
		m42 = 0.0f;
		m43 = -1.0f;
		m44 = 0.0f;

	}

	// left, right, bottom, top �����������ü����ϵľ���. 
	void Matrix4x4::setupFrustum(float left, float right, float bottom, float top, float near, float far) 
	{

		//���㹫��ֵ��

		float rl = right - left;
		float tb = top - bottom;
		float nf = near-far;

		assert(fabs(rl) > 0.00001);
		assert(fabs(tb) > 0.00001);
		assert(fabs(nf) > 0.00001);
		assert(near > 0.0f);
		assert(far > 0.0f);

		//ֱ�Ӹ�ֵ

		m11 = 2.0f*near/ rl;
		m12 = 0.0f;
		m13 = (right+left)/rl;
		m14 = 0.0f;

		m21 = 0.0f;
		m22 = 2.0f*near/ tb;
		m23 = (top+bottom)/tb;
		m24 = 0.0f;

	// OpenGL ʹ����������ϵ�� ��ͶӰ���еĵ�ֲ���Z��ĸ�����
	// �ر�ע�⺯�������е�near, far ����ֵ, zֵ�ı任Ӧ���Ǵ�[-far, -near] ��[1, -1] �����Ա任
	// �Ƶ����̣�
	// z' = (m33z+m34)/w , w = -z
	// ������� (z'=1, z= -far) �� (z'=-1, z= -near) ������ 
	// �Ϳ������m33, m34
		m31 = 0.0f;
		m32 = 0.0f;
		m33 = (far + near) / nf;
		m34 = 2*far*near / nf;

		m41 = 0.0f;
		m42 = 0.0f;
		m43 = -1.0f;
		m44 = 0.0f;

	}

	// �����* �������Ӿ��� �˷���˳��������ң� ��任˳���෴

	Matrix4x4 operator*(const Matrix4x4 &a, const Matrix4x4 &m) 
   {
		Matrix4x4 ret;

		ret.m11 = a.m11*m.m11 + a.m12*m.m21 + a.m13*m.m31 + a.m14*m.m41;
		ret.m12 = a.m11*m.m12 + a.m12*m.m22 + a.m13*m.m32 + a.m14*m.m42;
		ret.m13 = a.m11*m.m13 + a.m12*m.m23 + a.m13*m.m33 + a.m14*m.m43;
		ret.m14 = a.m11*m.m14 + a.m12*m.m24 + a.m13*m.m34 + a.m14*m.m44;

		ret.m21 = a.m21*m.m11 + a.m22*m.m21 + a.m23*m.m31 + a.m24*m.m41;
		ret.m22 = a.m21*m.m12 + a.m22*m.m22 + a.m23*m.m32 + a.m24*m.m42;
		ret.m23 = a.m21*m.m13 + a.m22*m.m23 + a.m23*m.m33 + a.m24*m.m43;
		ret.m24 = a.m21*m.m14 + a.m22*m.m24 + a.m23*m.m34 + a.m24*m.m44;

		ret.m31 = a.m31*m.m11 + a.m32*m.m21 + a.m33*m.m31 + a.m34*m.m41;
		ret.m32 = a.m31*m.m12 + a.m32*m.m22 + a.m33*m.m32 + a.m34*m.m42;
		ret.m33 = a.m31*m.m13 + a.m32*m.m23 + a.m33*m.m33 + a.m34*m.m43;
		ret.m34 = a.m31*m.m14 + a.m32*m.m24 + a.m33*m.m34 + a.m34*m.m44;

		ret.m41 = a.m41*m.m11 + a.m42*m.m21 + a.m43*m.m31 + a.m44*m.m41;
		ret.m42 = a.m41*m.m12 + a.m42*m.m22 + a.m43*m.m32 + a.m44*m.m42;
		ret.m43 = a.m41*m.m13 + a.m42*m.m23 + a.m43*m.m33 + a.m44*m.m43;
		ret.m44 = a.m41*m.m14 + a.m42*m.m24 + a.m43*m.m34 + a.m44*m.m44;

		return ret;
	}

	// �����*= ���ֺ�c++��׼�﷨һ�¡�

	Matrix4x4 &operator*= (Matrix4x4 &a, const Matrix4x4 &m) 
   {
		a = a*m;

		return a;
	}

}

