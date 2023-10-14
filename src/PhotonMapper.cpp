#pragma once
#include "../include/PhotonMapper.h"
#include "../include/Ray.h"
#include "../include/Scene.h"
#include "../include/glm/gtc/random.hpp"

void PhotonMapper::Map(Scene *scene, KDTree<Photon> &photonTree) {
  std::vector<Object *> transparentObjects;
  for (Object *o : scene->Objects) {
    if (o->getMaterial().getProperty() == MaterialProperty::translucence)
      transparentObjects.push_back(o);
  }
  std::vector<Photon> photons = std::vector<Photon>();
  for (Object *o : transparentObjects) {
    for (LightSource *l : scene->LightSources) {
      glm::vec3 planeCenter = o->getCenter();
      glm::vec3 n = glm::normalize(planeCenter - l->getCenter());
      glm::vec3 v1, v2;
      get2DPlaneBasis(n, v1, v2);
      for (unsigned int i = 0; i < photons_per_object; i++) {
        glm::vec3 p = l->GetRandomUniformPoint();
        if (Sphere *s = dynamic_cast<Sphere *>(o)) {
          Ray *ray = new Ray(
              p, glm::normalize(p - randomPointIn2DPlane(planeCenter, v1, v2,
                                                         s->getRadius())));
          ray->castPhoton(scene, ray, photons);
          delete ray;
        }
      }
    }
  }
  photonTree.buildTree(photons);
}

// Generate a random point in 3D space within a 2D plane defined by v1 and v2.
glm::vec3 randomPointIn2DPlane(const glm::vec3 &origin, const glm::vec3 &v1,
                               const glm::vec3 &v2, float radius) {
  float u = glm::linearRand(
      -1.0f, 1.0f); // Random value for the x-coordinate within [0, 1]
  float v = glm::linearRand(
      -1.0f, 1.0f); // Random value for the y-coordinate within [0, 1]

  if (u * u + v * v > 1.0f) {
    // Rescale the point to the unit circle
    float scale = 1.0f / glm::sqrt(u * u + v * v);
    u *= scale;
    v *= scale;
  }

  return origin + u * radius * v1 + v * radius * v2;
}

void get2DPlaneBasis(const glm::vec3 &normal, glm::vec3 &v1, glm::vec3 &v2) {
  // Handle the case when the normal is very close to (0, 0, 1) or (0, 0, -1)
  if (glm::length(glm::vec2(normal)) < 1e-5) {
    v1 = glm::vec3(1.0f, 0.0f, 0.0f);
    v2 = glm::vec3(0.0f, 1.0f, 0.0f);
  } else {
    // Choose an arbitrary vector not parallel to the normal
    glm::vec3 arbitraryVector(1.0f, 0.0f, 0.0f);

    // Calculate the first orthogonal vector
    v1 = glm::cross(arbitraryVector, normal);
    v1 = glm::normalize(v1);

    // Calculate the second orthogonal vector
    v2 = glm::cross(normal, v1);
  }
}