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
			hit.intersections = origin + direction * t;
			hit.distances = t;
			hit.normals = (hit.intersections - center).Normal();
			return true;
		}

		t = fmaxf(t1, t2);
		if (t > tmin)
		{
			hit.intersections = origin + direction * t;
			hit.distances = t;
			hit.normals = (hit.intersections - center).Normal();
			return true;
		}
	}
	else if (condition == 0)
	{
		// Tangency
		float t = -b + sqrtf(condition) / (2.f * a);

		if (t > tmin)
		{
			hit.intersections = origin + direction * t;
			hit.distances = t;
			hit.normals = (hit.intersections - center).Normal();
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
	/*const Vector3& cb = sphere.GetCenter();
	const Vector3& c1 = ray.GetOrigin();
	const Vector3& c2 = c1 + ray.GetDirection(); 
	const float rbrs = powf(sphere.GetRadius() + r, 2);

	const float a = (c2 - c1).LengthSquared();
	const float b = -2.f * (c2 - c1).Dot(cb - c1); //((cb * c1 - cb * c2 - c1 * c1 + c1 * c2) * 2.f).Sum();
	const float c = (cb - c1).LengthSquared() - rbrs; // (cb * cb - cb * c1 - c1 * c1).Sum() - rbrs;
		
	const float condition = (b * b) - (4.f * a * c);

	if (condition > 0)
	{
		// Intersection
		const float sqrtCond = sqrtf(condition);
		const float t1 = (-b + sqrtCond) / (2.f * a);
		const float t2 = (-b - sqrtCond) / (2.f * a);

		float t = fminf(t1, t2);
		if (t > 0.f)
		{
			const Vector3 solution(c1 + (c2 - c1) * t);
			/*if (fabs((solution - cb).LengthSquared() - rbrs) > FLT_EPSILON)
			{
				throw;
			}
			hit.intersections.push_back(solution);
			hit.distances.push_back(t);
			hit.normals.push_back((hit.intersections.back() - center).Normal());*/
		/*}

		t = fmaxf(t1, t2);
		if (t > 0.f)
		{
			const Vector3 solution(c1 + (c2 - c1) * t);
			/*if (fabs((solution - cb).LengthSquared() - rbrs) > FLT_EPSILON)
			{
				throw;
			}
			hit.intersections.push_back(solution);
			hit.distances.push_back(t);
			hit.normals.push_back((hit.intersections.back() - center).Normal());*/
		/*}
	}
	else if (condition == 0)
	{
		// Tangency
		float t = (-b + sqrtf(condition)) / (2.f * a);

		if (t > 0.f)
		{
			const Vector3 solution(c1 + (c2 - c1) * t);
			/*if (fabs((solution - cb).LengthSquared() - rbrs) > FLT_EPSILON)
			{
				throw;
			}
			hit.intersections.push_back(solution);
			hit.distances.push_back(t);
			hit.normals.push_back((hit.intersections.back() - center).Normal());*/
		/*}
	}
	
	return false; // hit.intersections.size() > 0;*/
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