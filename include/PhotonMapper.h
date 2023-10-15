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
public:
  static void Map(Scene *scene, KDTree<Photon> &photonTree,
                  unsigned int photons_per_object = 200);
  static ColorDBL calculatePhotonContribution(KDTree<Photon> &photonTree,
                                              glm::vec3 &center, double radius);

private:
};
glm::vec3 randomPointIn2DPlane(const glm::vec3 &origin, const glm::vec3 &v1,
                               const glm::vec3 &v2, float radius);

void get2DPlaneBasis(const glm::vec3 &normal, glm::vec3 &v1, glm::vec3 &v2);
