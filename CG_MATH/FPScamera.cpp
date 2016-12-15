#include "FPScamera.h"
#include "EulerAngles.h"
#include "MathUtil.h"

//�ƶ�λ��

void FPScamera::move(float front, float left, float up) {

	// ǰ���ƶ�

	
	Quaternion con_dir = conjugate(dir);

	if (fabs(front) > 0.0f) {
		
		// ��ȡ��ת���-z��

		Quaternion p;
		p.w = 0.0f; p.x = 0.0f; p.y = 0.0f; p.z = -1.0f;

		//���������ת�����������꣬ʹ��dir ������б任��
		p = conjugate(con_dir)*p*con_dir;

		// �ƶ�λ��pos

		pos += front*vector3(p.x, p.y, p.z);
	}

	// �����ƶ�

	if (fabs(left) > 0.0f) {

		// ��ȡ��ת���-x��

		Quaternion p;
		p.w = 0.0f; p.x = -1.0f; p.y = 0.0f; p.z = 0.0f;

		//���������ת�����������꣬ʹ��dir ������б任��
		p = conjugate(con_dir)*p*con_dir;

		//�ƶ�λ��pos

		pos += left*vector3(p.x, p.y, p.z);
	}

	// �����ƶ�

	if (fabs(up) > 0.0f) {

		//��ȡ��ת���y��

		Quaternion p;
		p.w = 0.0f; p.x = 0.0f; p.y = 1.0f; p.z = 0.0f;

		//���������ת�����������꣬ʹ��dir ������б任��
		p = conjugate(con_dir)*p*con_dir;

		//�ƶ�λ��pos

		pos += up*vector3(p.x, p.y, p.z);
	}


}

//ת������
//��λΪ�Ƕ�
// heading ��y����ת pitch ��x����ת�� bank ��z����ת

void FPScamera::rotate(float heading, float pitch, float bank) {

	// �����ת��Ԫ��

	Quaternion h, p, b;
	h.setToRotateAboutY(-heading / 180.0f*kPi);
	p.setToRotateAboutX(-pitch / 180.0f*kPi);
	b.setToRotateAboutZ(-bank / 180.0f*kPi);

	dir *= h*p*b;
}

//��ȡ�������

Matrix3x4 FPScamera::getMatrix() {
	Matrix3x4 m1, m2;
	m1.fromQuaternion(dir);
	m2.setupTanslation(-pos);

	//��ƽ�Ƶ���������ϵ������ת��������ϵ��
	return m1*m2;
}

