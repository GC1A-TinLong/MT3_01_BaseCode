#pragma once
#include <Novice.h>
#include <cmath>
#include <assert.h>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

struct Vector3 {
	float x, y, z;
};

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(float scalar, const Vector3& v);

float Dot(Vector3& v1, Vector3& v2);
float Length(const Vector3& v);
Vector3 Normailize(const Vector3& v);

struct Matrix4x4 {
	float m[4][4];
};

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4 Transpose(const Matrix4x4& m);
Matrix4x4 MakeIdentity4x4();
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
Matrix4x4 MakeRotateXMatrix(float& radian);
Matrix4x4 MakeRotateYMatrix(float& radian);
Matrix4x4 MakeRotateZMatrix(float& radian);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Matrix4x4& rotate, const Vector3& translate);
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);