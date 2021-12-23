#include "Dielectric.h"
#include "Hit.h"
#include "Ray.h"

Dielectric::Dielectric()
	: albedo(1.f, 1.f, 1.f)
	, refractionIndex(1.5f)
	, mt(123)
	, dist(0.f, .9999f)
{
}

Dielectric::Dielectric(const Vector3& albedo, float refractionIndex)
	: albedo(albedo)
	, refractionIndex(refractionIndex)
	, mt(123)
	, dist(0.f, 1.f)
{
}

bool Dielectric::Scatter(const Ray& in, const Hit& hit, Vector3& attenuation, Ray& out) const
{
	const Vector3& direction = in.GetDirection();
	Vector3 outNormal = hit.normal;
	Vector3 reflected = Reflect(direction, outNormal);
	float refractionIndex = 1.f / this->refractionIndex;
	float reflectionProbability = 1.f;
	float dirDotNormal = direction.Dot(outNormal);
	float cosine = -dirDotNormal;

	if (dirDotNormal > 0)
	{
		outNormal = -hit.normal;
		refractionIndex = this->refractionIndex;
		cosine = refractionIndex * dirDotNormal;
	}

	attenuation = albedo;
	Vector3 refracted;
	if (Refract(direction, outNormal, refractionIndex, refracted))
	{
		reflectionProbability = Schlick(cosine, this->refractionIndex);
	}

	if (dist(mt) < reflectionProbability)
	{
		out.Setup(hit.point, reflected);
	}
	else
	{
		out.Setup(hit.point, refracted);
	}

	return true;
}

Vector3 Dielectric::Reflect(const Vector3& in, const Vector3& normal) const
{
	return (in + normal * in.Dot(normal) * -2.f).Normal();
}

bool Dielectric::Refract(const Vector3& in, const Vector3& normal, float refractionRatio, Vector3& refracted) const
{
	float InDotNormal = in.Dot(normal);
	float discriminant = 1.f - refractionRatio * refractionRatio * (1.f - InDotNormal * InDotNormal);
	if (discriminant > 0)
	{
		refracted = ((in - (normal * InDotNormal)) * refractionRatio - normal * sqrtf(discriminant)).Normal();
		return true;
	}
	return false;
}

float Dielectric::Schlick(float cosine, float refractionIndex) const
{
	float r0 = powf((1.f - refractionIndex) / (1.f + refractionIndex), 2.f);
	return r0 + (1.f - r0) * powf(1.f - cosine, 5.f);
}
