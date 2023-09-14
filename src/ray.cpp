#pragma once
#include "../include/Ray.h"
#include "../include/Scene.h"
#include "../include/Object.h"

ColorDBL Ray::castRay(Scene* theScene, Ray* prevRay, float deathProbability) {

	//@TODO kolla igenom denna f�r optimering och f�rb�ttring
	// Loop for collision
	// If no collision return and set color to skybox
	// Calc nev ray
	// Send new ray

	float minDist = std::numeric_limits<float>::max();
	float newDist = std::numeric_limits<float>::max();
	bool hitsObject = false;
	bool oneHit = false;

	glm::vec3 intersectionPoint = glm::vec3();
	glm::vec3 newIntersectionPoint = glm::vec3();

	std::vector<Object*> theObjects = theScene->getoObjects();

	for (Object* aObject : theObjects) {
		if (aObject->Collision(this, newIntersectionPoint)) {
			hitsObject = true;

			newDist = std::abs(glm::length(newIntersectionPoint - orig));
			
			if (newDist <= minDist) {

				minDist = newDist;
				intersectionPoint = newIntersectionPoint;
				obj = aObject;

			}
		}
	}
	if (!hitsObject) {
		return theScene->SKYBOXCOLOR;
	}

	if (((double)rand() / (RAND_MAX)) <= deathProbability) {
		return obj->getMaterial().getColor(); //@TODO * imortance sen och r�kna med specul�ritet
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


