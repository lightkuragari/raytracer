#include "Sphere.h"
#include <math.h>

Sphere::Sphere(const Vector3& center, float radius, Material* material)
	: center(center)
	, r(radius)
	, material(material)
{
}

bool Sphere::RayVsSphere(const Ray& ray, Hit& hit, float radius) const
{
	const Vector3& origin = ray.GetOrigin();
	const Vector3& direction = ray.GetDirection();
	const Vector3 toCenter = center - origin;

	float a = direction.LengthSquared();
	float b = -2.f * direction.Dot(toCenter);
	float c = toCenter.LengthSquared() - (r + radius) * (r + radius);

	float condition = (b * b) - (4.f * a * c);

	hit.material = material;

	static const float tmin = .001f;

	if (condition > 0)
	{
		// Intersection
		float sqrtCond = sqrtf(condition);
		float t1 = (-b + sqrtCond) / (2.f * a);
		float t2 = (-b - sqrtCond) / (2.f * a);

		float t = fminf(t1, t2);
		if (t > tmin)
		{
			hit.point = origin + direction * t;
			hit.t = t;
			hit.normal = (hit.point - center).Normal();
			return true;
		}

		t = fmaxf(t1, t2);
		if (t > tmin)
		{
			hit.point = origin + direction * t;
			hit.t = t;
			hit.normal = (hit.point - center).Normal();
			return true;
		}
	}
	else if (condition == 0)
	{
		// Tangency
		float t = -b + sqrtf(condition) / (2.f * a);

		if (t > tmin)
		{
			hit.point = origin + direction * t;
			hit.t = t;
			hit.normal = (hit.point - center).Normal();
			return true;
		}
	}

	return false;
}

bool Sphere::IsHit(const Ray& ray, Hit& hit) const
{
	return RayVsSphere(ray, hit, 0.f);
}

bool Sphere::IsHitWithSphereRay(const Sphere& sphere, const Ray& ray, Hit& hit) const
{
	return RayVsSphere(ray, hit, sphere.GetRadius());
}

const Vector3& Sphere::GetCenter() const
{
	return center;
}

float Sphere::GetRadius() const
{
	return r;
}

void Sphere::SetPosition(const Vector3& position)
{
	center = position;
}