#include "FPScamera.h"
#include "EulerAngles.h"
#include "MathUtil.h"
#include "RotationMatrix.h"

//�ƶ�λ��

void FPScamera::move(float front, float left, float up) {

	RotationMatrix m;
	m.setup(dir);

	//��Ҫ�õ������������������ı�ʾ��
	// 1�� m �Ǵ��������굽��������ת����m��ת�ñ�ʾ������ת����
	// 2�� ������ת����������м�Ϊ���X Y Z ������������ı�ʾ��

	pos.x += -front*m.m31 - left*m.m11 + up*m.m21;
	pos.y += -front*m.m32 - left*m.m12 + up*m.m22;
	pos.z += -front*m.m33 - left*m.m13 + up*m.m23;
}

//ת������
//��λΪ�Ƕ�
// heading ��y����ת pitch ��x����ת�� bank ��z����ת

void FPScamera::rotate2D(float heading, float pitch) {

	//�Ƕ�ת����
	heading = heading / 180.0f*kPi;
	pitch = pitch / 180.0f*kPi;


	// �޸�heading�� ���Ʒ�Χ��[-Pi, Pi]
	dir.heading += heading;
	dir.heading = wrapPi(dir.heading);

	// �޸�pitch�� ���Ʒ�Χ��[-pi/2, pi/2]
	dir.pitch += pitch;
	if (dir.pitch < -kPi * 0.45f)
		dir.pitch = -kPi * 0.45f;
	else if (dir.pitch > kPi * 0.45f)
		dir.pitch = kPi * 0.45f;

}

//��ȡ�������

Matrix3x4 FPScamera::getMatrix() {
	
	Matrix3x4 m; 
	m.setupParentToLocal(pos, dir);
	
	return m;
}

