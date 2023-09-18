#pragma once
#include "../include/LightSource.h"
# define _PI 3.14159265358979323846

double LightSource::CheckShadowRays(Object* objectX, const glm::vec3& x) {

	float sum = 0.0;
	int N = 100;

	for (int i = 1; i <= N; i++) {
		float s = ((float)rand() / (RAND_MAX));
		float t = ((float)rand() / (RAND_MAX));

		if (s + t > 1) {
			s = 1 - s;
			t = 1 - t;
		}

		// Check if no collission V(x,y_i)


		glm::vec3 e1 = getP2() - getP0();
		glm::vec3 e2 = getP2() - getP0();

		glm::vec3 di = getP0() + e1 * s + e2 * t;

		float cosX = glm::dot(objectX->getNormal(), glm::normalize(di));
		float cosY = glm::dot(getNormal(), glm::normalize(di));
		sum += (cosX * cosY) / (glm::length(di) * glm::length(di));

	}
	sum = sum * 16 / (_PI * N);
	return 0.0;
}


