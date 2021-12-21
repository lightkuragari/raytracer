#pragma once

#include "Ray.h"
#include "Hit.h"
#include <memory>

class Material;

class Sphere : public Hitable
{
public:

	Sphere(const Vector3& center, float radius, Material* material);
	virtual bool IsHit(const Ray& ray, Hit& hit) const override;
	bool RayVsSphere(const Ray& ray, Hit& hit, float radius) const;
	bool IsHitWithSphereRay(const Sphere& sphere, const Ray& ray, Hit& hit) const;
	const Vector3& GetCenter() const;
	float GetRadius() const;

	void SetPosition(const Vector3& position);

protected:

	Vector3 center;
	float r;
	Material* material;
};