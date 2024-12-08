#pragma once

#include "raylib.h"
#include "raymath.h"

namespace sauna_math
{

typedef struct RotationAxisAngle
{
	float 	angle;
	Vector3 axis;
} RotationAxisAngle;

Matrix QuaternionToMatrix(Quaternion q)
{
	auto result = MatrixIdentity();

	float a2 = 2*(q.x*q.x), b2=2*(q.y*q.y), c2=2*(q.z*q.z);
    float ab = 2*(q.x*q.y), ac=2*(q.x*q.z), bc=2*(q.y*q.z);
    float ad = 2*(q.x*q.w), bd=2*(q.y*q.w), cd=2*(q.z*q.w);

	result.m0 = 1 - b2 - c2;
	result.m1 = ab + cd;
	result.m2 = ac - bd;

	result.m4 = ab - cd;
	result.m5 = 1 - a2 - c2;
	result.m6 = bc + ad;

	result.m8 = ac + bd;
	result.m9 = bc - ad;
	result.m10 = 1 - a2 - b2;

	return result;
}

}; // namespace sauna_math
