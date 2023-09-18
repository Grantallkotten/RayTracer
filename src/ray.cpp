#pragma once
#include "../include/Ray.h"
#include "../include/Scene.h"
#include "../include/Object.h"


ColorDBL Ray::castRay(Scene* scene, Ray* prevRay, float deathProbability) {
	// Är prevRay nödvändig?

	float minDist = std::numeric_limits<float>::max();
	float newDist = std::numeric_limits<float>::max();
	bool hitsObject = false;

	glm::vec3 intersectionPoint = glm::vec3();
	glm::vec3 newIntersectionPoint = glm::vec3();

	for (Object* aObject : scene->Objects) {
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
		return scene->SKYBOXCOLOR;
	}

	if (((double)rand() / (RAND_MAX)) <= deathProbability) {
		return obj->getMaterial().getColor(); //@TODO * imortance sen och räkna med speculäritet
	}

	//@TODO Rekursiv formel

	return ColorDBL(0.0f, 0.0f, 0.2f);
}


