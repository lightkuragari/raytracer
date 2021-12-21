#include "Ray.h"

Ray::Ray()
{
}

Ray::Ray(const Vector3& origin, const Vector3& direction)
	: origin(origin)
	, direction(direction)
{
}

void Ray::Setup(const Vector3& origin, const Vector3& direction)
{
	this->origin = origin;
	this->direction = direction;
}

const Vector3& Ray::GetOrigin() const
{
	return origin;
}

const Vector3& Ray::GetDirection() const
{
	return direction;
}