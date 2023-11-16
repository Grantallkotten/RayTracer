#pragma once
#include "ColorDBL.h"
#include "Material.h"
#include "PhotonMapper.h"
#include "kdtree.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

class Object;
class Scene;

class Ray {
private:
  glm::vec3 orig = glm::vec3(); // point of light sorce for photon. Often used
  // symbol: po or ps
  glm::vec3 end = glm::vec3(); // Often used symbol: pe
  glm::vec3 dir = glm::vec3(); // pixels postion in the plane - camaras position
  Object *obj = nullptr; // sould be a pointer to the surfes of the objekt the
  // ray is going to
  Ray *prev = nullptr;
  Ray *next = nullptr;
  ColorDBL color;
  bool inObject = false;
  // Remember to normilaze all directions!
public:
  Ray(){};

  Ray(const glm::vec3 &origin, const glm::vec3 &direction,
      bool inObject = false)
      : orig(origin), dir(direction), inObject{inObject} {}

  glm::vec3 getDir() const { return dir; }

  glm::vec3 getOrig() const { return orig; }

  ColorDBL castRay(Scene *scene, KDTree<Photon> &photons,
                   float deathProbability, Ray *prevRay = nullptr);

  bool ShadowRay(Scene *scene, MaterialProperty &objMaterialType);

  void castPhoton(Scene *scene, Ray *prevRay, KDTree<Photon> &photons);
  void reflectPhoton(Scene *scene, KDTree<Photon> &photons);
  void photonTranslucent(Scene *scene, KDTree<Photon> &photons);

  ColorDBL inderectLight(Scene *scene, KDTree<Photon> &photons,
                         float deathProbability);

  ColorDBL reflectionLight(Scene *scene, KDTree<Photon> &photons,
                           float deathProbability);

  ColorDBL reflectionLightTranslucence(Scene *scene, KDTree<Photon> &photons,
                                       float deathProbability);

  ColorDBL getColor() { return color; }

  void setColor(ColorDBL c) { color = c; }

  void rayColor() { std::cout << color; };

  void setInObject(bool b) { inObject = b; }

  bool getInObject() { return inObject; }
};

void creatLocalAxes(glm::vec3 &e1, glm::vec3 &e2, glm::vec3 &e3,
                    const glm::vec3 &normal, const glm::vec3 &dir);
