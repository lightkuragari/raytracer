#pragma once

#include "Vector3.h"

class Ray
{
public:

	Ray();
	Ray(const Vector3& origin, const Vector3& direction);

	void Setup(const Vector3& origin, const Vector3& direction);

	const Vector3& GetDirection() const;
	const Vector3& GetOrigin() const;

protected:

	Vector3 origin;
	Vector3 direction;
};