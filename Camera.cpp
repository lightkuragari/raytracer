#include "Camera.h"
#include "Sphere.h"
#include "Hit.h"
#include <iostream>

Camera::Camera(const Vector3& position, const Vector3& lookAt, float focalDistance, const Vector3& up)
	: resolutionX(1024)
	, resolutionY(1024)
	, samples(100)
	, lensWidth(1.f)
	, lensHeight(lensWidth * resolutionY / resolutionX)
	, focalDistance(focalDistance)
	, position(position)
	, up(up)
	, mt(7)
	, dist(0.f, .9999f)
{
	direction = (lookAt - position).Normal();
	right = direction.Cross(up);
}

void Camera::Render(const std::vector<Hitable*>& list) const
{
	std::cout << "P3" << std::endl;
	std::cout << "# Raytracer render" << std::endl;
	std::cout << resolutionX << " " << resolutionY << std::endl;
	std::cout << 255 << std::endl;

	for (int y = 0; y < resolutionY; ++y)
	{
		for (int x = 0; x < resolutionX; ++x)
		{
			Vector3 color;
			Ray ray;
			for (int s = 0; s < samples; ++s)
			{
				float dx = s > 0.f ? dist(mt) : 0.f;
				float dy = s > 0.f ? dist(mt) : 0.f;

				GetScreenRay((float)x + dx, (float)y + dy, ray);
				color += GetColor(ray, list, 0);
			}

			color /= (float)samples;
			std::cout << (int)(color.R() * 255.99f) << " " << (int)(color.G() * 255.99f) << " " << (int)(color.B() * 255.99f);

			if (x < resolutionX - 1)
				std::cout << "    ";			
		}

		if (y < resolutionY - 1)
			std::cout << std::endl;
	}
}

Vector3 Camera::GetColor(const Ray& ray, const std::vector<Hitable*>& world, int depth) const
{
	Vector3 color;
	Hit closest;
	closest.t = FLT_MAX;

	if (depth >= 50)
	{
		return color;
	}

	bool wasHit = false;
	for (size_t i = 0; i < world.size(); ++i)
	{
		int rootsCount = 0;
		Hit hit;
		if (world[i]->IsHit(ray, hit))
		{
			wasHit = true;
			if (hit.t < closest.t)
			{
				closest = hit;
			}
		}
	}

	if (wasHit)
	{
		Vector3 attenuation;
		Ray scatter;

		if (closest.material->Scatter(ray, closest, attenuation, scatter))
		{
			color = attenuation * GetColor(scatter, world, depth + 1);
		}

		return color;
	}
	else
	{
		// Get scene uv coords from ray direction and camera parameters.
		Vector3 c = ray.GetDirection();
		c /= c.Dot(direction * focalDistance);
		c -= direction * focalDistance;
		c /= (up / lensWidth + right / lensHeight);
		c += .5f;

		float v = fmax(0.f, fmin(1.f, c.Y()));

		static const Vector3 white(255.f, 255.f, 255.f);
		static const Vector3 sky(122.f, 122.f, 255.f);

		color += (white / 255.f * (1.f - v)) + (sky / 255.f * v);
	}

	return color;
}

void Camera::GetScreenRay(float x, float y, Ray& outRay) const
{
	float u = x / resolutionX;
	float v = (resolutionY - y) / resolutionY;
	Vector3 c(u, v, .5f);
	c -= .5f;

	Vector3 rayDirection = ((direction * focalDistance) + ((up / lensWidth + right / lensHeight) * c)).Normal();
	outRay.Setup(position, rayDirection);
}