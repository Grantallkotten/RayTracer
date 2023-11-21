#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

namespace rtu {
inline glm::vec3 randomPointOnHemisphere() {
  float zAxisPosition = glm::linearRand(0.0f, 1.0f);
  float cosOmega_i = std::sqrt(zAxisPosition); // Ensuring z0 is positive
  float sinOmega_i = std::sqrt(1.0f - zAxisPosition);
  float phi_i = glm::linearRand(
      0.0f, static_cast<float>(M_PI_2)); // Randomize phi_i again
  return glm::vec3(sinOmega_i * std::cos(phi_i), sinOmega_i * std::sin(phi_i),
                   cosOmega_i);
}

inline void creatLocalAxes(glm::vec3 &e1, glm::vec3 &e2, glm::vec3 &e3,
                           const glm::vec3 &normal, const glm::vec3 &dir) {
  e3 = normal;
  e1 = glm::normalize(-dir + glm::dot(normal, dir) * normal);
  e2 = glm::cross(e3, e1);
}

inline float hemispherePDF(float theta) {
  if (theta < 0 || theta > M_PI / 2) {
    return 0.0f; // Outside the valid range of theta for the upper hemisphere
  } else {
    return (1.0f / (2.0f * M_PI)) * sin(theta); // PDF calculation
  }
}

inline float incomingAngle(const glm::vec3 &rayDirection,
                           const glm::vec3 &surfaceNormal) {

  // Calculate the dot product of the two normalized vectors
  float dotProduct =
      glm::dot(glm::normalize(rayDirection), glm::normalize(surfaceNormal));

  // Calculate the angle using the arccosine function
  float angle = std::acos(dotProduct);

  // Return the angle in radians
  return angle;
}
} // namespace rtu
