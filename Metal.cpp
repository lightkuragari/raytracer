#include "Metal.h"
#include "Hit.h"
#include "Ray.h"

Metal::Metal()
	: albedo(.5f)
	, fuzziness(1.f)
	, mt(546)
	, dist(-1.f, 1.f)
{
}

Metal::Metal(const Vector3& albedo, float fuzzyness)
	: albedo(albedo)
	, fuzziness(fuzzyness)
	, mt(546)
	, dist(-1.f, 1.f)
{
}

bool Metal::Scatter(const Ray& in, const Hit& hit, Vector3& attenuation, Ray& out) const
{
	Vector3 reflected = Reflect(in.GetDirection(), hit.normals);
	// Generate random point based on unit sphere over the normal of the hit point.
	Vector3 scatter;
	do
	{
		scatter = Vector3(dist(mt), dist(mt), dist(mt));
	} while (scatter.LengthSquared() > 1.f);

	Vector3 target = hit.intersections + reflected + scatter * fuzziness;
	out.Setup(hit.intersections, (target - hit.intersections).Normal());
	attenuation = albedo;	

	return out.GetDirection().Dot(hit.normals) > 0.f;
}

Vector3 Metal::Reflect(const Vector3& in, const Vector3& normal) const
{
	return (in + normal * in.Dot(normal) * -2.f).Normal();
}