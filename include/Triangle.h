#pragma once
#include <iostream>
#include <vector>
#include "../include/ColorDBL.h"
#include "../include/Polygon.h"
#include "../include/glm/glm.hpp"

class Triangle : public Polygon{
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
			point1{ p1 }, point2{ p2 }, point3{ p3 }, normal{getNormal()}
		{}

		glm::vec3 getNormal();

		ColorDBL getColor() const { return color; }

};

