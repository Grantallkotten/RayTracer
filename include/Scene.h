#pragma once
#include <iostream>
#include <vector>
#include "../include/ColorDBL.h"
#include "../include/glm/glm.hpp"

class Ray {
private:
	glm::vec3 orig = glm::vec3(0.0f, 0.0f, 0.0f);// point of light sorce for photon
	glm::vec3 dir = glm::vec3(0.0f, 0.0f, 0.0f);
	Ray* surf = nullptr; // sould be a pointer to the surfes of the objekt the ray is going to
	Ray* prev = nullptr;
	Ray* next = nullptr;
	ColorDBL color = ColorDBL(255.0, 0.0, 0.0);

public:
	Ray() {};

	Ray(const glm::vec3& origin, const glm::vec3& direction) : orig(origin), dir(direction) {}

	glm::vec3 at(float t) const {
		return orig + t * dir;
	}

	ColorDBL getColor() { return color; }

	void rayColor() { 
		std::cout << color; 
	};
};

