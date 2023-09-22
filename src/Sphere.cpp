#include "../include/Sphere.h"

bool Sphere::Collision(Ray *ray, glm::vec3 &intersectionPoint) {
  const float EPSILON = 0.000001f;

  glm::vec3 dir = ray->getDir();
  glm::vec3 start = ray->getOrig();
  glm::vec3 cs = start - centerPoint;
  float a = glm::dot(dir, dir);
  float half_b = glm::dot(cs, dir);
  float c = glm::dot(cs, cs) - radius * radius;

  float arg = half_b * half_b - a * c;

  if (arg < -EPSILON) {
    return false;
  }
  if (arg < EPSILON) {
    intersectionPoint = ray->at(-half_b);
  }
  auto sqrt_arg = glm::sqrt(arg);
  auto t = (-half_b - sqrt_arg) / a;
  if (t <= Ray::T_MIN || t >= Ray::T_MAX) {
    t = (-half_b + sqrt_arg) / a;
    if (t <= Ray::T_MIN || t >= Ray::T_MAX) {
      return false;
    }
  }

  // std::cout << "t: " << t << " :\n";

  // glm::vec3 x_rt = ray->getOrig() + ray->getDir() * t;
  //  glm::vec3 surfNormal = glm::normalize(x_rt - centerPoint);

  intersectionPoint = ray->at(t);

  // std::cout <<  " " << t;
  // std::cout << "\n" << intersectionPoint.x << ", " << intersectionPoint.y <<
  // ", " << intersectionPoint.z;

  return true;
}
