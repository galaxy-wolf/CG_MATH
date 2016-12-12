#include "Camera.h"
#include "EulerAngles.h"

//�ƶ�λ��

void Camera::move(float front, float left, float up) {

	// ǰ���ƶ�

	if (fabs(front) > 0.0f) {
		
		// ��ȡ��ת���-z��

		Quaternion p;
		p.w = 0.0f; p.x = 0.0f; p.y = 0.0f; p.z = -1.0f;

		p = conjugate(dir)*p*dir;

		// �ƶ�λ��pos

		pos += front*vector3(p.x, p.y, p.z);
	}

	// �����ƶ�

	if (fabs(left) > 0.0f) {

		// ��ȡ��ת���-x��

		Quaternion p;
		p.w = 0.0f; p.x = -1.0f; p.y = 0.0f; p.z = 0.0f;

		p = conjugate(dir)*p*dir;

		//�ƶ�λ��pos

		pos += left*vector3(p.x, p.y, p.z);
	}

	// �����ƶ�

	if (fabs(up) > 0.0f) {

		//��ȡ��ת���y��

		Quaternion p;
		p.w = 0.0f; p.x = 0.0f; p.y = 1.0f; p.z = 0.0f;

		p = conjugate(dir)*p*dir;

		//�ƶ�λ��pos

		pos += up*vector3(p.x, p.y, p.z);
	}


}

//ת������
//��λΪ����
// heading ��y����ת pitch ��x����ת�� bank ��z����ת

void Camera::rotate(float heading, float pitch, float bank) {

	// �����ת��Ԫ��
	
	Quaternion h, p, b;
	h.setToRotateAboutY(heading);
	p.setToRotateAboutX(pitch);
	b.setToRotateAboutZ(bank);

	dir *= h*p*b;
}

//��ȡ�������

Matrix3x4 Camera::getMatrix() {
	Matrix3x4 m1, m2;
	m1.fromQuaternion(conjugate(dir));
	m2.setTranslation(-pos);

	//��ƽ�Ƶ���������ϵ������ת��������ϵ��
	return m1*m2;
}

