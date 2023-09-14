#pragma once
#include <iostream>
#include <vector>
#include "ColorDBL.h"
#include "glm/glm.hpp"
#include "Object.h"
#include "Material.h"


class Triangle : public Object {
private:
	glm::vec3 point0;
	glm::vec3 point1;
	glm::vec3 point2;
	glm::vec3 normal;
	Material material;
	float roughness = 1.0f;
	float emission = 0.0f;

public:

	Triangle(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const Material& m = Material(1.0, 0.0, 0.0, ColorDBL(255.0, 0.0, 0.0))) :
		point0{ p0 }, point1{ p1 }, point2{ p2 }, material{ m }// Måste kolla så alla points lägger sig med högerhandsregeln 
	{ calcNormal(); }

	void calcNormal();

	glm::vec3 getNormal() override{ return normal; }

	Material getMaterial() override { return material; }

	bool Collistion(Ray* ray, glm::vec3& intersectionPoint) override;

};
