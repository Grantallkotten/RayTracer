#pragma once
#include "../include/glm/glm.hpp"
#include "../include/ColorDBL.h"
#include "../include/Ray.h"
#include "../include/Material.h"

class Object {
  private:
  public:

  //Object() {};

  virtual glm::vec3 getNormal(glm::vec3 point) = 0;

  virtual Material getMaterial() = 0;

  virtual bool Collision(Ray *ray, glm::vec3& intersectionPoint) = 0;

};
