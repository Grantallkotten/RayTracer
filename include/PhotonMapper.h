#pragma once
#include "ColorDBL.h"
#include "glm/glm.hpp"
#include "kdtree.h"

class Scene;
struct Photon {
  glm::vec3 pos;
  ColorDBL color;
};
class PhotonMapper {
  PhotonMapper(unsigned int photons_per_object = 200)
      : photons_per_object{photons_per_object} {};

public:
  void Map(Scene *scene, KDTree<Photon> &photonTree);

private:
  unsigned int photons_per_object;
  Photon castPhoton();
};

glm::vec3 randomPointIn2DPlane(const glm::vec3 &origin, const glm::vec3 &v1,
                               const glm::vec3 &v2, float radius);

void get2DPlaneBasis(const glm::vec3 &normal, glm::vec3 &v1, glm::vec3 &v2);
