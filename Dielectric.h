#pragma once

#include <random>
#include "Material.h"
#include "Vector3.h"

class Dielectric : public Material
{
public:
	Dielectric();
	Dielectric(const Vector3& albedo, float refractionIndex);

	virtual bool Scatter(const class Ray& in, const struct Hit& hit, class Vector3& attenuation, Ray& out) const override;

protected:

	Vector3 Reflect(const Vector3& in, const Vector3& normal) const;
	bool Refract(const Vector3& in, const Vector3& normal, float refractionRatio, Vector3& refracted) const;
	float Schlick(float cosine, float refractionIndex) const;

	Vector3 albedo;
	float refractionIndex;

	// Random number generator
	mutable std::mt19937 mt;
	mutable std::uniform_real_distribution<float> dist;
};
