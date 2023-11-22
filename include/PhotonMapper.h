#pragma once
#include "ColorDBL.h"
#include "kdtree.h"
#include <glm/glm.hpp>

class Scene;
class Sphere;
class Object;
struct Photon {
  glm::vec3 position;
  glm::vec3 direction;
  ColorDBL color;
};

class PhotonMapper {
public:
  static void Map(Scene *scene, KDTree<Photon> &photonTree,
                  unsigned int photons_per_object = 200);
  static ColorDBL calculatePhotonContribution(KDTree<Photon> &photonTree,
                                              glm::vec3 &center, float radius);

private:
  static void mapPhotonsForObject(Scene *scene, Object *obj,
                                  KDTree<Photon> &photonTree,
                                  unsigned int photons_per_object);
  static void mapPhotonForSphere(Scene *scene, Sphere *sphere,
                                 const glm::vec3 &objectCenter,
                                 const glm::vec3 &lightToObjectDir,
                                 const glm::vec3 &x_s, const glm::vec3 &y_l,
                                 const glm::vec3 &x_l, float lightArea,float radiance,
                                 KDTree<Photon> &photonTree,
                                 unsigned int photons_per_object);
};

glm::vec3 randomPointIn2DPlane(const glm::vec3 &origin, const glm::vec3 &v1,
                               const glm::vec3 &v2, float radius);

void get2DPlaneBasis(const glm::vec3 &normal, glm::vec3 &v1, glm::vec3 &v2);
