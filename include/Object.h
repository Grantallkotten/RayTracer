#pragma once
#include "../include/ColorDBL.h"
#include "../include/Material.h"
#include "../include/Ray.h"
#include "../include/glm/glm.hpp"

class Object {
private:
public:
  // Object() {};

  virtual glm::vec3 getNormal(const glm::vec3 &intersection_point) = 0;

  virtual Material getMaterial() = 0;

  virtual bool Collision(Ray *ray, glm::vec3 &intersectionPoint) = 0;
};
