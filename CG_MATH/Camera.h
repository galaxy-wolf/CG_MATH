#pragma once

#include "vector3.h"
#include "Quaternion.h"
#include "Matrix3x4.h"

using namespace CG_MATH;

class Camera
{
public:

	//公共数据
	
	vector3 pos;
	Quaternion dir;


	//公共操作

	// 初始化相机位置，世界坐标原点，朝向-Z轴。

	Camera() :pos(0.0f, 0.0f, 0.0f), dir(kQuaternionIdentity) {}
	
	//移动位置

	void move(float front, float left, float up);

	//转动方向

	void rotate(float heading, float pitch, float bank);

	//获取相机矩阵

	Matrix3x4 getMatrix();
};

