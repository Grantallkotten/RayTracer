#include "../include/Sphere.h"

bool Sphere::Collision(Ray *ray, glm::vec3 &intersectionPoint) {
  const float EPSILON = 0.000001f;

  glm::vec3 D = ray->getDir();
  glm::vec3 S = ray->getOrig();

  float c1 = glm::dot(D, D);
  float c2 = glm::dot(2.0f * D, (S - centerPoint));
  float c3 = glm::dot((S - centerPoint), (S - centerPoint)) - radius * radius;
  float arg = c2 * c2 - 4.0f * c1 * c3;

  if (arg < -EPSILON) {
    return false;
  }
  float t;

  if (arg > -EPSILON && arg < EPSILON) {
    t = -c2 / (2 * c1);
  } else {
    // t = std::min( ( -c2 - std::abs(arg)) / (2 * c1), (-c2 + std::abs(arg)) /
    // (2 * c1));
    t = (-c2 - std::abs(arg)) / (2 * c1);
  }
  if (t < 0.0f) {
    return false;
  }
  // std::cout << "t: " << t << " :\n";

  glm::vec3 x_rt = ray->getOrig() + ray->getDir() * t;
  // glm::vec3 surfNormal = glm::normalize(x_rt - centerPoint);

  intersectionPoint = x_rt;

  // std::cout <<  " " << t;
  // std::cout << "\n" << intersectionPoint.x << ", " << intersectionPoint.y <<
  // ", " << intersectionPoint.z;

  return true;
}
