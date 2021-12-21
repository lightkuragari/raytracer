#include "Camera.h"
#include "Sphere.h"
#include "Lambert.h"
#include "Metal.h"

int main(int argc, char** argv)
{
	Camera c(Vector3(0.f, 0.f, 1.f), Vector3(0.f, 0.f, 0.f));
	std::vector<Hitable*> list =
	{
		new Sphere(Vector3(0.f, 1.f, -10.f), 2.f, new Lambert(Vector3(.2f, .2f, 1.f))),
		new Sphere(Vector3(-4.f, 1.f, -9.f), 2.f, new Metal(Vector3(1.f, 1.f, 1.f), .5f)),
		new Sphere(Vector3(4.f, 1.f, -10.f), 2.f, new Metal(Vector3(1.f, .2f, .2f), 0.f)),
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
			sphere->SetPosition(hit.intersections);
		}
	}

	c.Render(list);
}