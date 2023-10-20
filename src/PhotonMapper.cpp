#include "../include/PhotonMapper.h"
#include "../include/Ray.h"
#include "../include/Scene.h"
#include "../include/glm/gtc/random.hpp"

void PhotonMapper::Map(Scene *scene, KDTree<Photon> &photonTree,
                       unsigned int photons_per_object) {
  std::vector<Object *> transparentObjects;
  for (Object *o : scene->Objects) {
    if (o->getMaterial().getProperty() == MaterialProperty::translucence)
      transparentObjects.push_back(o);
  }
  std::vector<Photon> photons = std::vector<Photon>();
  std::cout << "Mapping Photons!" << std::endl;
  std::cout << photons_per_object << ": Photons per object!" << std::endl;
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
              p, glm::normalize(
                     randomPointIn2DPlane(planeCenter, v1, v2, s->getRadius()) -
                     p));
          ray->setColor(ColorDBL(1, 1, 1));
          ray->castPhoton(scene, ray, photons);
          delete ray;
        }
      }
    }
  }
  std::cout << "Photon count: " << photons.size() << std::endl;
  std::cout << "Building KDTree" << std::endl;
  photonTree.buildTree(photons);
  std::cout << "Photon Mapping Complete" << std::endl;
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

// Function to calculate the contribution of photons within a radius around each
// data point
ColorDBL PhotonMapper::calculatePhotonContribution(KDTree<Photon> &photonTree,
                                                   glm::vec3 &center,
                                                   double radius) {
  ColorDBL totalContribution(0, 0, 0);

  // Query the KD-tree for photons within the specified radius
  std::vector<Photon> nearbyPhotons = photonTree.rangeSearch(center, radius);

  // Calculate the contribution of each nearby photon and accumulate it
  for (const Photon &photon : nearbyPhotons) {
    totalContribution += photon.color;
  }
  return totalContribution;
}
