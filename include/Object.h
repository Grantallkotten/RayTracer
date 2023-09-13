#pragma once

#include "glm/glm.hpp"
#include "ColorDBL.h"
#include "Ray.h"

class Object {
  private:
  public:

  //Object() {};

  virtual glm::vec3 getNormal() = 0;

  virtual ColorDBL getColor() = 0;

  virtual bool Collistion(const Ray* ray, glm::vec3& intersectionPoint, float& dist) = 0;

};
