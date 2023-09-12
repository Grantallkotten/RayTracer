#pragma once

#include "glm/glm.hpp"
#include "ColorDBL.h"
#include "Ray.h"

class Object {
  private:
  public:
  Object() {};
  virtual glm::vec3 Normal();
  virtual ColorDBL Color();
  virtual glm::vec3 Collistion(const Ray* ray);
};
