#include "../include/Sphere.h"

bool Sphere::Collision(Ray *ray, CollisionInfo& collisionInfo) {
  const float EPSILON = 0.00001f;
#if 1
  glm::vec3 D = ray->getDir();
  glm::vec3 S = ray->getOrig();
  glm::vec3 SC = S - centerPoint;
  float c1 = glm::dot(D, D);
  float c2 = glm::dot(2.0f * D, SC);
  float c3 = glm::dot(SC, SC) - radius * radius;
  float arg = c2 * c2 - 4.0f * c1 * c3;

  if (arg < EPSILON) {
      return false;
  }
  float t;
  
  if (arg > -EPSILON && arg < EPSILON) {
    t = -c2 / (2 * c1);
  } else {
    // t = std::min( ( -c2 - std::abs(arg)) / (2 * c1), (-c2 + std::abs(arg)) /
    t = (-c2 - std::sqrt(arg)) / (2.0f * c1);
  }

  if (t <= EPSILON || t > 1000.0f) {
    return false;
  }

  collisionInfo.point = ray->getOrig() + ray->getDir() * t;
  collisionInfo.normal = getNormal(collisionInfo.point);
  //if (ray->insideObject()) { collisionInfo.normal - collisionInfo.normal; }
  // glm::vec3 surfNormal = glm::normalize(intersectionPoint - centerPoint);

  //intersectionPoint = x_rt;
  return true;
#endif
}
