#include "Camera.h"
#include "EulerAngles.h"

//移动位置

void Camera::move(float front, float left, float up) {

	// 前后移动

	if (fabs(front) > 0.0f) {
		
		// 获取旋转后的-z轴

		Quaternion p;
		p.w = 0.0f; p.x = 0.0f; p.y = 0.0f; p.z = -1.0f;

		p = conjugate(dir)*p*dir;

		// 移动位置pos

		pos += front*vector3(p.x, p.y, p.z);
	}

	// 左右移动

	if (fabs(left) > 0.0f) {

		// 获取旋转后的-x轴

		Quaternion p;
		p.w = 0.0f; p.x = -1.0f; p.y = 0.0f; p.z = 0.0f;

		p = conjugate(dir)*p*dir;

		//移动位置pos

		pos += left*vector3(p.x, p.y, p.z);
	}

	// 上下移动

	if (fabs(up) > 0.0f) {

		//获取旋转后的y轴

		Quaternion p;
		p.w = 0.0f; p.x = 0.0f; p.y = 1.0f; p.z = 0.0f;

		p = conjugate(dir)*p*dir;

		//移动位置pos

		pos += up*vector3(p.x, p.y, p.z);
	}


}

//转动方向
//单位为弧度
// heading 绕y轴旋转 pitch 绕x轴旋转， bank 绕z轴旋转

void Camera::rotate(float heading, float pitch, float bank) {

	// 获得旋转四元数
	
	Quaternion h, p, b;
	h.setToRotateAboutY(heading);
	p.setToRotateAboutX(pitch);
	b.setToRotateAboutZ(bank);

	dir *= h*p*b;
}

//获取相机矩阵

Matrix3x4 Camera::getMatrix() {
	Matrix3x4 m1, m2;
	m1.fromQuaternion(conjugate(dir));
	m2.setTranslation(-pos);

	//先平移到惯性坐标系，再旋转到视坐标系。
	return m1*m2;
}

