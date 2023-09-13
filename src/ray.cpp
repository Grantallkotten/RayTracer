#pragma once
#include "../include/Ray.h"

Ray* Ray::castRay(Scene* theScene, Ray* prevRay, bool lastRay) {

	//@TODO kolla igenom denna för optimering och förbättring
	// Loop for collision
	// If no collision return and set color to skybox
	// Calc nev ray
	// Send new ray

	float dist = std::numeric_limits<float>::max();
	float distNew = std::numeric_limits<float>::max();
	bool hitsObject = false;

	glm::vec3 intersectionPoint;
	glm::vec3 newIntersectionPoint;


	for (Object* aObject : (*theScene).getoObjects()) {
		hitsObject = (*aObject).Collistion(this, intersectionPoint, distNew);
		if (hitsObject) {
			if (distNew < dist) {
				dist = distNew;
				intersectionPoint = newIntersectionPoint;
				color += (*aObject).getColor();
			}
		}
	}
	if (!hitsObject) {
		return this;
	}
	/*
	// Test collision
	// Creat a new outgoing vec
	glm::vec3 newDir = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 newOrig = glm::vec3(1.0f, 0.0f, 0.0f);

	Ray nextRay = Ray(newOrig, newDir);

	if (false) {// lastRay == false
		next = nextRay.castRay(theScene, this, true);
	}
	*/

	return this;
}


