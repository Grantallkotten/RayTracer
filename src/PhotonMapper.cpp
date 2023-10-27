#include "../include/PhotonMapper.h"
#include "../include/Ray.h"
#include "../include/Scene.h"
#include "../include/glm/gtc/random.hpp"

const float PI = 3.14159265358979323846f;

void PhotonMapper::Map(Scene* scene, KDTree<Photon>& photonTree,
	unsigned int photons_per_object) {
	std::vector<Object*> transparentObjects;
	for (Object* o : scene->Objects) {
		if (o->getMaterial().getProperty() == MaterialProperty::translucence)
			transparentObjects.push_back(o);
	}
	std::vector<Photon> photons = std::vector<Photon>();
	std::cout << "Mapping Photons!" << std::endl;
	std::cout << photons_per_object << ": Photons per object!" << std::endl;
	for (Object* o : transparentObjects) {
		for (LightSource* l : scene->LightSources) {
			glm::vec3 C = o->getCenter();
			auto M = l->getCenter();
			glm::vec3 N_d = glm::normalize(C - M);
			glm::vec3 d = M - C;
			glm::vec3 y_l, x_l;
			get2DPlaneBasis(N_d, y_l, x_l);
			for (unsigned int i = 0; i < photons_per_object; i++) {
				glm::vec3  x_s = l->GetRandomUniformPoint();
				if (Sphere* s = dynamic_cast<Sphere*>(o)) {
					auto x_e = randomPointIn2DPlane(C, y_l, x_l, s->getRadius());
					float A = l->getArea();
					auto phi_T = PI * A * glm::vec3(1.0f, 1.0f, 1.0f);
					auto G_m = glm::dot(glm::vec3(0,0,-1), glm::normalize(-d)) / (d * d);
					auto A_s = G_m * PI * s->getRadius() * s->getRadius();
					auto phi_e = phi_T * G_m * A_s / (2 * PI);
					auto flux = phi_e / (float)photons_per_object;

					Ray* ray = new Ray(x_s, glm::normalize(x_e - x_s));
					ray->setColor(ColorDBL(flux.x, flux.y, flux.z));
					ray->castPhoton(scene, ray, photons);
					delete ray;
				}
			}
		}
	}
	std::cout << "Photon count: " << photons.size() << std::endl;
	std::cout << "Building KDTree" << std::endl;
	photonTree.buildTree(photons);
	std::cout << "Photon Mapping Complete" << std::endl;
}

// Generate a random point in 3D space within a 2D plane defined by v1 and v2.
glm::vec3 randomPointIn2DPlane(const glm::vec3& C, const glm::vec3& y_l,
	const glm::vec3& x_l, float radius) {

	float r_i = radius/glm::sqrt(glm::linearRand(0.0f, 1.0f));
	float phi_i = glm::linearRand(0.0f, 2.0f * PI);
	float a = r_i * glm::cos(phi_i);
	float b = r_i * glm::sin(phi_i);

	return C + a * x_l + b * y_l;
}

void get2DPlaneBasis(const glm::vec3& z_l, glm::vec3& y_l, glm::vec3& x_l) {
	// Handle the case when the normal is very close to (0, 0, 1) or (0, 0, -1)
	if (glm::length(glm::vec2(z_l)) < 1e-5) {
		y_l = glm::vec3(1.0f, 0.0f, 0.0f);
		x_l = glm::vec3(0.0f, 1.0f, 0.0f);
	}
	else {
		// Choose an arbitrary vector not parallel to the normal
		glm::vec3 x_w(1.0f, 0.0f, 0.0f);

		// Calculate the first orthogonal vector
		y_l = glm::cross(z_l, x_w);
		y_l = glm::normalize(y_l);

		// Calculate the second orthogonal vector
		x_l = glm::cross(y_l, z_l);
	}
}

// Function to calculate the contribution of photons within a radius around each
// data point
ColorDBL PhotonMapper::calculatePhotonContribution(KDTree<Photon>& photonTree,
	glm::vec3& center,
	double radius) {
	ColorDBL totalContribution(0, 0, 0);
	double totalWeight = 0.0;

	// Query the KD-tree for photons within the specified radius
	std::vector<Photon> nearbyPhotons = photonTree.rangeSearch(center, radius);

	// Calculate the contribution of each nearby photon and accumulate it
	for (const Photon& photon : nearbyPhotons) {
		double distance = glm::length(photon.pos - center);
		// Calculate a weight based on the distance (might be worth experimenting
		// with weight function)
		double weight = 1.0 / (distance + 0.001); // Adjust the function as needed

		totalContribution += photon.color * weight;
		totalWeight += weight;
	}

	// Normalize the total contribution by the sum of weights to get the weighted
	// average
	if (totalWeight != 0.0) {
		totalContribution /= totalWeight;
	}

	return totalContribution;
}
