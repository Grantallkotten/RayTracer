#pragma once
#include "../include/Ray.h"
#include "../include/Scene.h"
#include "../include/Object.h"
class LightSource;


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

			newDist = glm::length(newIntersectionPoint - orig);
			
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
	double lightContribution = 0.0;
	ColorDBL returnColor = obj->getMaterial().getColor();

	if (((double)rand() / (RAND_MAX)) <= deathProbability) {
		
		for (LightSource* aLightSource : scene->LightSources) {
			lightContribution = aLightSource->CheckShadowRays(scene, obj, intersectionPoint);
			// @TODO sätt lightContribution på färgen av objektet
			returnColor *= lightContribution;
		}
		
		return returnColor; //@TODO * imortance sen och räkna med speculäritet
	}

	//@TODO Rekursiv formel

	return ColorDBL(0.0f, 0.0f, 0.2f);
}

bool Ray::ShadowRay(Scene* scene) {
	float dist_x_to_yi = glm::length(dir);
	float dist_x_to_ip = std::numeric_limits<float>::max();
	glm::vec3 intersectionPoint = glm::vec3();

	for (Object* obj : scene->Objects) {
		if (obj->Collision(this, intersectionPoint)) {
			dist_x_to_ip = glm::length(intersectionPoint - orig);
			if (dist_x_to_ip < dist_x_to_yi) {// Använda pointers till objekt istället?
					return false;
			}
			//else { return true; }
		}
	}
	return true;
}


