#pragma once
#include "Triangle.h"
#include "Sphere.h"

class scene;
class LightSource : public Triangle {
private:
	double radiance;
public:
	LightSource(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const Material& m = Material(Material::diffusion, ColorDBL(1.0, 0.0, 0.0)), double radiance = 150) : Triangle(p0, p1, p2, m), radiance{ radiance } {
}
double getRadiance() { return radiance; }

double CheckShadowRays(Scene* scene, Object* objectX, const glm::vec3& x);
};

