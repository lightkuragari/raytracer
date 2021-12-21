#pragma once

#include "Material.h"
#include <vector>
#include <memory>

struct Hit
{
	Vector3 intersections;
	Vector3 normals;
	float distances;
	Material* material;
};

class Hitable
{
public:
	virtual bool IsHit(const Ray& ray, Hit& hit) const = 0;
};