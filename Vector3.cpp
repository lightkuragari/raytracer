#include "Vector3.h"
#include <cmath>

Vector3::Vector3()
	: v{ 0.f, 0.f, 0.f }
{
}

Vector3::Vector3(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

Vector3::Vector3(float val)
{
	v[0] = v[1] = v[2] = val;
}

Vector3::Vector3(const Vector3& vector)
{
	v[0] = vector.X();
	v[1] = vector.Y();
	v[2] = vector.Z();
}

float Vector3::Length() const
{
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float Vector3::LengthSquared() const
{
	return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

float Vector3::Dot(const Vector3& other) const
{
	return (v[0] * other.X() + v[1] * other.Y() + v[2] * other.Z()) / Length();
}

Vector3 Vector3::Cross(const Vector3& other) const
{
	return Vector3(
		v[1] * other.Z() - v[2] * other.Y(),
		v[2] * other.X() - v[0] * other.Z(),
		v[0] * other.Y() - v[1] * other.X()
	);
}

float Vector3::Sum() const
{
	return v[0] + v[1] + v[2];
}

Vector3 Vector3::operator+() const
{
	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-v[0], -v[1], -v[2]);
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(v[0] + other.X(), v[1] + other.Y(), v[2] + other.Z());
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(v[0] - other.X(), v[1] - other.Y(), v[2] - other.Z());
}

Vector3 Vector3::operator*(const Vector3& other) const
{
	return Vector3(v[0] * other.X(), v[1] * other.Y(), v[2] * other.Z());
}

Vector3 Vector3::operator/(const Vector3& other) const
{
	return Vector3(v[0] / other.X(), v[1] / other.Y(), v[2] / other.Z());
}

Vector3 Vector3::operator+(const float& other) const
{
	return Vector3(v[0] + other, v[1] + other, v[2] + other);
}

Vector3 Vector3::operator-(const float& other) const
{
	return Vector3(v[0] - other, v[1] - other, v[2] - other);
}

Vector3 Vector3::operator*(const float& other) const
{
	return Vector3(v[0] * other, v[1] * other, v[2] * other);
}

Vector3 Vector3::operator/(const float& other) const
{
	return Vector3(v[0] / other, v[1] / other, v[2] / other);
}

void Vector3::operator+=(const Vector3& other)
{
	v[0] += other.X();
	v[1] += other.Y();
	v[2] += other.Z();
}
void Vector3::operator-=(const Vector3& other)
{
	v[0] -= other.X();
	v[1] -= other.Y();
	v[2] -= other.Z();
}

void Vector3::operator*=(const Vector3& other)
{
	v[0] *= other.X();
	v[1] *= other.Y();
	v[2] *= other.Z();
}

void Vector3::operator/=(const Vector3& other)
{
	v[0] /= other.X();
	v[1] /= other.Y();
	v[2] /= other.Z();
}

Vector3 Vector3::Normal() const
{
	return *this / Length();
}

void Vector3::Normalize()
{
	float l = Length();
	v[0] /= l;
	v[1] /= l;
	v[2] /= l;
}

float Vector3::X() const
{
	return v[0];
}

float Vector3::Y() const
{
	return v[1];
}

float Vector3::Z() const
{
	return v[2];
}

float Vector3::R() const
{
	return v[0];
}

float Vector3::G() const
{
	return v[1];
}

float Vector3::B() const
{
	return v[2];
}