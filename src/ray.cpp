#pragma once
#include "../include/Ray.h"

ColorDBL Ray::castRay(Scene* theScene, Ray* prevRay, float deathProbability) {

	//@TODO kolla igenom denna för optimering och förbättring
	// Loop for collision
	// If no collision return and set color to skybox
	// Calc nev ray
	// Send new ray

	float minDist = std::numeric_limits<float>::max();
	float newDist = std::numeric_limits<float>::max();
	bool hitsObject = false;

	glm::vec3 intersectionPoint;
	glm::vec3 newIntersectionPoint;


	for (Object* aObject : theScene->getoObjects()) {
		hitsObject = aObject->Collistion(this, intersectionPoint);
		
		if (hitsObject) {
			if (newDist < minDist) {
				minDist = newDist;
				intersectionPoint = newIntersectionPoint;
				obj = aObject;
			}
		}
	}
	if (!hitsObject) {
		return theScene->SKYBOXCOLOR;
	}

	if (((double)rand() / (RAND_MAX)) + 1 <= deathProbability) {
		return obj->getMaterial().getColor(); //@TODO * imortance sen och räkna med speculäritet
	}


	// Calc new dir


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

	return ColorDBL(0.0f, 0.0f, 0.2f);
}


