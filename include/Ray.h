#pragma once
#include "ColorDBL.h"
#include "glm/glm.hpp"
#include <iostream>
#include <vector>

class Object;
class Scene;

class Ray {
private:
  glm::vec3 orig = glm::vec3(); // point of light sorce for photon. Often used
                                // symbol: po or ps
  glm::vec3 end = glm::vec3();  // Often used symbol: pe
  glm::vec3 dir = glm::vec3(); // pixels postion in the plane - camaras position
  Object *obj = nullptr; // sould be a pointer to the surfes of the objekt the
                         // ray is going to
  Ray *prev = nullptr;
  Ray *next = nullptr;
  ColorDBL color;
  // Remember to normilaze all directions!
public:
  static constexpr float T_MIN = 0.0f;
  static constexpr float T_MAX = 10000.0f;
  Ray(){};

  Ray(const glm::vec3 &origin, const glm::vec3 &direction)
      : orig(origin), dir(direction) {}

  glm::vec3 getDir() const { return dir; }

  glm::vec3 getOrig() const { return orig; }

  glm::vec3 at(float t) { return orig * dir * t; }

  ColorDBL castRay(Scene *scene, Ray *prevRay, float deathProbability);

  bool ShadowRay(Scene *scene);

  ColorDBL getColor() { return color; }

  void rayColor() { std::cout << color; };
};
