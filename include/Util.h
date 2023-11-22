#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2 6.28318530718
#endif


namespace rtu {
    // Probability density function (PDF) for cosine-weighted sampling on a hemisphere
    float PDF_CosineWeighted(float Omega) {
        // Assuming Omega is in radians
        return std::cos(Omega) / M_PI;
    }

    // Function to generate a random point on a hemisphere with cosine-weighted sampling
    inline glm::vec3 randomPointOnHemisphere(float& pdf) {
        float y_i = glm::linearRand(0.0f, 1.0f);
        float cosOmega = std::sqrt(y_i);
        float sinOmega = std::sqrt(1.0f - y_i);
        float phi = y_i * M_PI_2;

        pdf = PDF_CosineWeighted(std::acos(cosOmega)); // Calculate the PDF at this Omega

        return glm::vec3(sinOmega * std::cos(phi), sinOmega * std::sin(phi), cosOmega) * pdf;
    }

glm::vec3 BRDF(const glm::vec3& normal, float& pdf) {
    glm::vec3 sampleDirection = glm::ballRand(1.0f); // Sample direction uniformly within a unit sphere

    // Align the sample direction with the surface normal
    glm::vec3 bitangent = glm::cross(normal, glm::vec3(1.0f, 0.0f, 0.0f));
    if (glm::length(bitangent) < 0.01f) {
        bitangent = glm::cross(normal, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    bitangent = glm::normalize(bitangent);

    glm::vec3 tangent = glm::cross(normal, bitangent);
    glm::mat3 tangentToWorld = glm::mat3(bitangent, tangent, normal);
    sampleDirection = tangentToWorld * sampleDirection;

    // Calculate the PDF for cosine-weighted sampling
    pdf = glm::max(0.0f, glm::dot(sampleDirection, normal)) / M_PI;

    return sampleDirection;
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
