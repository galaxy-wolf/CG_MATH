#pragma once

namespace CG_MATH
{

	class vector3;
	class EulerAngles;
	class Quaternion;
	class RotationMatrix;

	//--------------------------------------------------------------------------------------
	//Matrix3*4��
	// ʵ��3*4ת�������ܹ�����κ�3D����任

	class Matrix3x4
	{
	public:
		
		// ��������

		// �����ֵ
		//ǰ3�а������Ա任�����һ�а���ƽ��

		float m11, m12, m13, tx;
		float m21, m22, m23, ty;
		float m31, m32, m33, tz;

		// ��������

		//��Ϊ��λ����

		void identity();

		// ֱ�ӷ���ƽ�Ʋ���

		void zeroTanslation();
		void setTranslation(const vector3 &d);
		void setupTanslation(const vector3 &d);

		// ����ִ�и��ռ� <->�ֲ��ռ�任�ľ��󣬼ζ��ֲ��ռ���ָ����λ�úͷ�λ�� �÷�λ������ʹ��ŷ���ǻ���ת�����ʾ�ġ�

		void setupLocalToParent(const vector3 &pos, const EulerAngles &orient);
		void setupLocalToParent(const vector3 &pos, const RotationMatrix &orient);
		void setupParentToLocal(const vector3 &pos, const EulerAngles &orient);
		void setupParentToLocal(const vector3 &pos, const RotationMatrix &orient);

		// ��������������ת�ľ���

		void setupRotate(int axis, float theta);

		// ��������������ת�ľ���

		void setupRotate(const vector3 &axis, float theta);

		//������ת���󣬽�λ������Ԫ����ʽ����

		void fromQuaternion(const Quaternion &q);

		// ���������������ŵľ���

		void setupScale(const vector3 &s);

		// ���������������ŵľ���

		void setupScaleAlongAxis(const vector3 &axis, float k);

		// �����б����

		void setupShear(int axis, float s, float t);

		// ����ͶӰ���� ͶӰƽ���ԭ��

		void setupProject(const vector3 &n);

		// ���췴�����

		void setupReflect(int axis, float k = 0.0f);

		// ����������ƽ�淴��ľ���

		void setupReflect(const vector3 &n);

	};

	// �����* �����任������Ӿ��󣬳˷���˳��������ң���任˳���෴��

	vector3 operator*(const Matrix3x4 &m, const vector3 &p);
	Matrix3x4 operator*(const Matrix3x4 &a, const Matrix3x4 &m);

	// �����*= ���ֺ�c++��׼�﷨��һ����

	//vector3 &operator*=(const Matrix3x4 &m, const vector3 &p);
	Matrix3x4 &operator*=(Matrix3x4 &a, const Matrix3x4 &m);


	// ����3x3 ���ֵ�����ʽ
	float determinant(const Matrix3x4 &m);

	//����������

	Matrix3x4 inverse(const Matrix3x4 &m);

	// ��ȡ�����ƽ�Ʋ���

	vector3 getTranslation(const Matrix3x4 &m);

	// �Ӿֲ�����->������ �� ������->�ֲ����� ȡλ��/��λ

	vector3 getPositionFromParentToLocalMatrix(const Matrix3x4 &m);
	vector3 getPositionFromLocalToParentMatrix(const Matrix3x4 &m);

}


