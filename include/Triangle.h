#pragma once
#include <iostream>
#include <vector>
#include "ColorDBL.h"
#include "glm/glm.hpp"
#include "Object.h"

class Triangle : public Object {
private:
	glm::vec3 point1;
	glm::vec3 point2;
	glm::vec3 point3;
	glm::vec3 normal;
	ColorDBL color;
	float roughness = 1.0f;
	float emission = 0.0f;
public:

	Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const ColorDBL& c = ColorDBL(1.0, 0.0, 0.0)) :
		point1{ p1 }, point2{ p2 }, point3{ p3 }, normal{Normal()}
	{}

	glm::vec3 Normal() override;

	ColorDBL Color() override { return color; }
	glm::vec3 Collistion(const Ray* ray, out glm::vec3 point) override;

};
