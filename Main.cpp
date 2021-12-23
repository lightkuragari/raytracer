#include "Camera.h"
#include "Sphere.h"
#include "Lambert.h"
#include "Metal.h"
#include "Dielectric.h"

int main(int argc, char** argv)
{
	Camera c(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f));

	Sphere* internalSphere = new Sphere(Vector3(-1.f, 1.f, -5.f), -.9f, new Dielectric(Vector3(.85f, 1.f, .85f), 1.5f));
	Sphere* externalSphere = new Sphere(Vector3(-1.f, 1.f, -5.f), 1.f, new Dielectric(Vector3(.85f, 1.f, .85f), 1.5f));

	std::vector<Hitable*> list =
	{
		new Sphere(Vector3(0.f, 1.f, -10.f), 2.f, new Lambert(Vector3(.2f, .2f, 1.f))),
		new Sphere(Vector3(-4.f, 1.f, -7.5f), 2.f, new Metal(Vector3(1.f, 1.f, 1.f), .5f)),
		new Sphere(Vector3(4.f, 1.f, -10.f), 2.f, new Metal(Vector3(1.f, .2f, .2f), 0.f)),
		externalSphere,
		internalSphere,
		new Sphere(Vector3(2.f, 1.f, -7.5f), .5f, new Dielectric(Vector3(1.f, 1.f, .5f), 1.5f)),
		new Sphere(Vector3(0.f, -52.f, -10.f), 50.f, new Lambert())
	};

	Sphere* floor = dynamic_cast<Sphere*>(list.back());

	// Sit all spheres on top of the base sphere
	for (size_t i = 0; i < list.size() - 1; ++i)
	{
		Sphere* sphere = dynamic_cast<Sphere*>(list[i]);

		if (sphere == nullptr)
		{
			continue;
		}

		Ray ray(sphere->GetCenter(), Vector3(0.f, -1.f, 0.f));
		Hit hit;
		if (floor->IsHitWithSphereRay(*sphere, ray, hit))
		{
			sphere->SetPosition(hit.point);
		}
	}

	internalSphere->SetPosition(externalSphere->GetCenter());

	c.Render(list);
}
