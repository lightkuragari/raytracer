#pragma once

#include "Ray.h"
#include <random>

class Sphere;
class Hitable;

class Camera
{
public:

	Camera(const Vector3& position, const Vector3& lookAt, float focalDistance = 1.f, const Vector3& up = Vector3(0.f, 1.f, 0.f));

	void Render(const std::vector<Hitable*>& world) const;
	Vector3 GetColor(const Ray& ray, const std::vector<Hitable*>& world, int depth) const;

	void GetScreenRay(float x, float y, Ray& outRay) const;

protected:

	int resolutionX;
	int resolutionY;

	int samples;

	float lensWidth;
	float lensHeight;
	float focalDistance;

	Vector3 position;
	Vector3 direction;
	Vector3 up;
	Vector3 right;

	// Random number generator
	mutable std::mt19937 mt;
	std::uniform_real_distribution<float> dist;
};