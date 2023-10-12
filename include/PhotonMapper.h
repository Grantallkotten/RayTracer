#pragma once
#include "glm/glm.hpp"
#include "kdtree.h"
#include "Scene.h";

struct Photon {
	glm::vec3 pos;
	double radiance;
};
class PhotonMapper {
	PhotonMapper(unsigned int photons_per_object = 200) : photons_per_object{ photons_per_object } {};
public:
	KDTree<Photon> Map(Scene scene) {};
private:
	unsigned int photons_per_object;
	Photon castPhoton();
};

glm::vec3 randomPointIn2DPlane(const glm::vec3& origin, const glm::vec3& v1, const glm::vec3& v2, float radius);

void get2DPlaneBasis(const glm::vec3& normal, glm::vec3& v1, glm::vec3& v2);
