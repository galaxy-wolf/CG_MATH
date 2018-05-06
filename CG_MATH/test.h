#pragma once

#include <directxmath.h>
#include <iostream>

#include "EulerAngles.h"
#include "MathUtil.h"
#include "Matrix3x4.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include "RotationMatrix.h"
#include "vector3.h"

int testAllFile();
void redirectOutPut();

void setMatrix(const CG_MATH::Matrix4x4& m);
void setRowMatrix(const CG_MATH::Matrix4x4& m);
void mulMatrix(const CG_MATH::Matrix4x4& m);
void DrawObject();
void DrawAxis(const CG_MATH::vector3& p);
std::ostream& operator<<(std::ostream &os, const CG_MATH::Matrix4x4& m);
void QuaternionSlerpTest();
void QuaternionPowTest();
