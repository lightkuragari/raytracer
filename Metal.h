#pragma once

#include <random>
#include "Material.h"
#include "Vector3.h"

class Metal : public Material
{
public:
	Metal();
	Metal(const Vector3& albedo, float fuzziness);

	virtual bool Scatter(const Ray& in, const Hit& hit, Vector3& attenuation, Ray& out) const override;

protected:

	Vector3 Reflect(const Vector3& in, const Vector3& normal) const;

	Vector3 albedo;
	float fuzziness;

	// Random number generator
	mutable std::mt19937 mt;
	mutable std::uniform_real_distribution<float> dist;
};
