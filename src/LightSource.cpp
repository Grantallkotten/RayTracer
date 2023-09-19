#pragma once
#include "../include/LightSource.h"
#include <random>
# define _PI 3.14159265358979323846

std::default_random_engine seed;
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);


double LightSource::CheckShadowRays(Object* objectX, const glm::vec3& x) {

	float sum = 0.0;
	int N = 100;
	glm::vec3 e1 = getP1() - getP0();
	glm::vec3 e2 = getP2() - getP0();
	float A = glm::length(e1) * glm::length(e2);
	glm::vec3 Ny = getNormal();
	glm::vec3 Nx = objectX->getNormal();

	if (typeid(*objectX) == typeid(LightSource)) {
		return 1.0;
	}

	for (int i = 1; i <= N; i++) {
		float s = ((float)rand() / (RAND_MAX));
		float t = ((float)rand() / (RAND_MAX));

		if (s + t > 1) {
			s = 1 - s;
			t = 1 - t;
		}

		// @TODO Check if no collission V(x,y_i)
		// Skippa att kolla om objektet blockar för sig själv mot ett ljus

		glm::vec3 yi = getP0() + s * e1 + t* e2;

		glm::vec3 di = yi - x;

		float cosX = glm::dot(Ny, di/glm::length(di));
		float cosY = -glm::dot(Nx, di / glm::length(di));

		sum += std::max(0.0f, (cosX * cosY) / (glm::length(di) * glm::length(di)));

	}
	float BRDF = 1.0f / _PI;
	sum = (float)(A * BRDF * radiance / N * sum);


	return sum;
}


