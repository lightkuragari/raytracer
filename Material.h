#pragma once

class Material
{
public:
	virtual bool Scatter(const class Ray& in, const struct Hit& hit, class Vector3& attenuation, Ray& out) const = 0;
};