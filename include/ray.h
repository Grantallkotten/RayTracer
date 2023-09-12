#pragma once
#include <iostream>
#include <vector>
#include "../include/ColorDBL.h"
#include "../include/glm/glm.hpp"

class Ray {
private:
	glm::vec3 orig = glm::vec3();// point of light sorce for photon. Often used symbol: po or ps
	glm::vec3 end = glm::vec3(); // Often used symbol: pe
	glm::vec3 dir = glm::vec3(); // pixels postion in the plane - camaras position
	Ray* surf = nullptr; // sould be a pointer to the surfes of the objekt the ray is going to
	Ray* prev = nullptr;
	Ray* next = nullptr;
	ColorDBL color = ColorDBL(255.0, 0.0, 0.0);
	// Remember to normilaze all directions!
public:
	Ray() {};

	Ray(const glm::vec3& origin, const glm::vec3& direction) : orig(origin), dir(direction) {}

	glm::vec3 at(float t) const {
		return orig + t * dir;
	}

	glm::vec3 getDir() const { return dir; }

	glm::vec3 getOrig() const { return orig; }

	//@TODO gör en rekursiv formel som retunerar en ray (next) och tar in en ray (prev)

	ColorDBL getColor() { return color; }

	void rayColor() { 
		std::cout << color; 
	};
};

