#pragma once

#include "Material.h"
#include <vector>
#include <memory>

struct Hit
{
	Vector3 point;
	Vector3 normal;
	float t;
	Material* material;
};

class Hitable
{
public:
	virtual bool IsHit(const Ray& ray, Hit& hit) const = 0;
};