#pragma once
#include <iostream>
#include <vector>
#include "ColorDBL.h"
#include "glm/glm.hpp"
#include "Object.h"

class Triangle : public Object {
private:
	glm::vec3 point0;
	glm::vec3 point1;
	glm::vec3 point2;
	glm::vec3 normal;
	ColorDBL color;
	float roughness = 1.0f;
	float emission = 0.0f;

public:

	Triangle(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const ColorDBL& c = ColorDBL(1.0, 0.0, 0.0)) :
		point0{ p0 }, point1{ p1 }, point2{ p2 }, normal{getNormal()}// Måste kolla så alla points lägger sig med högerhandsregeln
	{}

	void calcNormal();

	ColorDBL getColor() override { return color; }

	bool Collistion(const Ray* ray, glm::vec3& intersectionPoint, float& dist) override;

};
