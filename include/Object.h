#pragma once
#include "../include/ColorDBL.h"
#include "../include/Material.h"
#include "../include/Ray.h"
#include "../include/glm/glm.hpp"

struct CollisionInfo {
	glm::vec3 normal;
	glm::vec3 point;
};

class Object {
private:
public:
  // Object() {};

  virtual glm::vec3 getNormal(glm::vec3 point) = 0;

  virtual Material getMaterial() = 0;

  virtual bool Collision(Ray *ray, CollisionInfo &collisionInfo) = 0;

  virtual glm::vec3 getCenter() = 0;
};
