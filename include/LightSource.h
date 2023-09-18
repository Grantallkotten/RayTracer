#pragma once
#include "Triangle.h"


class LightSource : public Triangle {
private:
	double radiance;
public:
	LightSource(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const Material& m = Material(1.0, 0.0, 0.0, ColorDBL(1.0, 0.0, 0.0)), double radiance = 0.5) : Triangle(p0, p1, p2, m), radiance { radiance } {
}
float getRadiance() { return radiance; }

double CheckShadowRays(Object* objectX, const glm::vec3& x);

};

