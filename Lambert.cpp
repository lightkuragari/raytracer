#include "Lambert.h"
#include "Ray.h"
#include "Hit.h"

Lambert::Lambert()
	: albedo(.5f)
	, mt(546)
	, dist(-1.f, 1.f)
{
}

Lambert::Lambert(const Vector3& albedo)
	: albedo(albedo)
	, mt(546)
	, dist(-1.f, 1.f)
{
}

bool Lambert::Scatter(const Ray& in, const Hit& hit, Vector3& attenuation, Ray& out) const
{
	// Generate random point based on unit sphere over the normal of the hit point.
	Vector3 scatter;
	do
	{
		scatter = Vector3(dist(mt), dist(mt), dist(mt));
	} while (scatter.LengthSquared() > 1.f);

	Vector3 target = hit.intersections + hit.normals + scatter;
	out.Setup(hit.intersections, (target - hit.intersections).Normal());
	attenuation = albedo;
	return true;
}