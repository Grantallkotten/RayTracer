#pragma once
#include "../include/Ray.h"
#include "../include/Scene.h"
#include "../include/Object.h"

<<<<<<< Updated upstream
Ray* Ray::castRay(Scene* theScene, Ray* prevRay, bool lastRay) {

=======
ColorDBL Ray::castRay(Scene* theScene, Ray* prevRay, float deathProbability) {
>>>>>>> Stashed changes
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


<<<<<<< Updated upstream
	for (Object* aObject : (*theScene).getoObjects()) {
		hitsObject = (*aObject).Collistion(this, intersectionPoint, distNew);
=======
	for (Object* aObject : theScene->getObjects()) {
		hitsObject = aObject->Collistion(this, intersectionPoint);
		
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	/*
=======

	if (((double)rand() / (RAND_MAX)) + 1 <= deathProbability) {
		return obj->getMaterial().getColor(); //@TODO * imortance sen och räkna med speculäritet
	}


	// Calc new dir


	
>>>>>>> Stashed changes
	// Test collision
	// Creat a new outgoing vec
	glm::vec3 newDir = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 newOrig = glm::vec3(1.0f, 0.0f, 0.0f);

	Ray nextRay = Ray(newOrig, newDir);

	if (false) {// lastRay == false
		//next = *nextRay->castRay(theScene, this, true);
	}
	

	return this;
}


