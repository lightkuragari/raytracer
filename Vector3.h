#pragma once

#ifndef VECTOR_H
#define VECTOR_H

class Vector3
{
public:

	Vector3();
	Vector3(float x, float y, float z);
	Vector3(float val);
	Vector3(const Vector3& vector);

	float Length() const;
	float LengthSquared() const;
	float Dot(const Vector3& other) const;
	Vector3 Cross(const Vector3& other) const;
	float Sum() const;

	Vector3 operator+() const;
	Vector3 operator-() const;

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(const Vector3& other) const;
	Vector3 operator/(const Vector3& other) const;

	Vector3 operator+(const float& other) const;
	Vector3 operator-(const float& other) const;
	Vector3 operator*(const float& other) const;
	Vector3 operator/(const float& other) const;

	void operator+=(const Vector3& other);
	void operator-=(const Vector3& other);
	void operator*=(const Vector3& other);
	void operator/=(const Vector3& other);

	Vector3 Normal() const;
	void Normalize();

	float X() const;
	float Y() const;
	float Z() const;
	float R() const;
	float G() const;
	float B() const;

protected:

	float v[3];
};

#endif