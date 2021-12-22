#pragma once

#include "Material.h"
#include "Vector3.h"
#include <random>

class Lambert : public Material
{
public:

	Lambert();
	Lambert(const Vector3& albedo);
	virtual bool Scatter(const Ray& in, const Hit& hit, Vector3& attenuation, Ray& out) const override;

protected:

	Vector3 albedo;

	// Random number generator
	mutable std::mt19937 mt;
	mutable std::uniform_real_distribution<float> dist;
};
