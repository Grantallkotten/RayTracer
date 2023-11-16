#include "../include/PhotonMapper.h"
#include "../include/Ray.h"
#include "../include/Scene.h"
#include <glm/gtc/random.hpp>

const float PI = 3.14159265358979323846f;

void PhotonMapper::Map(Scene *scene, KDTree<Photon> &photonTree,
                       unsigned int photons_per_object) {
  std::vector<Object *> transparentObjects;
  for (Object *obj : scene->Objects) {
    if (obj->getMaterial().getProperty() == MaterialProperty::translucence)
      transparentObjects.push_back(obj);
  }

  std::cout << "Mapping Photons!" << std::endl;
  std::cout << photons_per_object << ": Photons per object!" << std::endl;
  for (Object *obj : transparentObjects) {
    mapPhotonsForObject(scene, obj, photonTree, photons_per_object);
  }
  std::cout << "Photon Mapping Complete" << std::endl;
}
void PhotonMapper::mapPhotonsForObject(Scene *scene, Object *obj,
                                       KDTree<Photon> &photonTree,
                                       unsigned int photons_per_object) {
  for (LightSource *l : scene->LightSources) {
    glm::vec3 C = obj->getCenter();
    glm::vec3 M = l->getCenter();
    glm::vec3 N_d = glm::normalize(C - M);

    glm::vec3 y_l, x_l;
    get2DPlaneBasis(N_d, y_l, x_l);
    for (std::size_t i = 0; i < photons_per_object; i++) {
      glm::vec3 x_s = l->GetRandomUniformPoint();
      float lightArea = l->getArea();
      if (Sphere *sphere = dynamic_cast<Sphere *>(obj)) {
        mapPhotonForSphere(scene, sphere, M, N_d, x_s, y_l, x_l, lightArea,
                           photonTree, photons_per_object);
      }
    }
  }
}

void PhotonMapper::mapPhotonForSphere(
    Scene *scene, Sphere *sphere, const glm::vec3 &objectCenter,
    const glm::vec3 &lightToObjectDir, const glm::vec3 &x_s,
    const glm::vec3 &y_l, const glm::vec3 &x_l, float lightArea,
    KDTree<Photon> &photonTree, unsigned int photons_per_object) {
  float sphereRadius = sphere->getRadius();
  glm::vec3 x_e = randomPointIn2DPlane(objectCenter, y_l, x_l, sphereRadius);

  glm::vec3 phi_T = PI * lightArea * glm::vec3(1.0f, 1.0f, 1.0f);

  float G_m = glm::dot(glm::vec3(0, 0, -1), -lightToObjectDir) /
              glm::dot(lightToObjectDir, lightToObjectDir);
  float A_s = G_m * PI * sphereRadius * sphereRadius;
  glm::vec3 phi_e = phi_T * G_m * A_s / (2 * PI);
  glm::vec3 flux = phi_e / static_cast<float>(photons_per_object);

  Ray *ray = new Ray(x_s, glm::normalize(x_e - x_s));
  ray->setColor(ColorDBL(flux.x, flux.y, flux.z));
  ray->castPhoton(scene, ray, photonTree);
  delete ray;
}

// Generate a random point in 3D space within a 2D plane defined by v1 and v2.
glm::vec3 randomPointIn2DPlane(const glm::vec3 &C, const glm::vec3 &y_l,
                               const glm::vec3 &x_l, float radius) {

  float r_i = radius / glm::sqrt(glm::linearRand(0.0f, 1.0f));
  float phi_i = glm::linearRand(0.0f, 2.0f * PI);
  float a = r_i * glm::cos(phi_i);
  float b = r_i * glm::sin(phi_i);

  return C + a * x_l + b * y_l;
}

void get2DPlaneBasis(const glm::vec3 &z_l, glm::vec3 &y_l, glm::vec3 &x_l) {
  // Handle the case when the normal is very close to (0, 0, 1) or (0, 0, -1)
  if (glm::length(glm::vec2(z_l)) < 1e-5) {
    y_l = glm::vec3(1.0f, 0.0f, 0.0f);
    x_l = glm::vec3(0.0f, 1.0f, 0.0f);
  } else {
    // Choose an arbitrary vector not parallel to the normal
    glm::vec3 x_w(1.0f, 0.0f, 0.0f);

    // Calculate the first orthogonal vector
    y_l = glm::cross(z_l, x_w);
    y_l = glm::normalize(y_l);

    // Calculate the second orthogonal vector
    x_l = glm::cross(y_l, z_l);
  }
}

// Function to calculate the contribution of photons within a radius around
// each data point
ColorDBL PhotonMapper::calculatePhotonContribution(KDTree<Photon> &photonTree,
                                                   glm::vec3 &center,
                                                   double radius) {
  ColorDBL totalContribution(0, 0, 0);
  double totalWeight = 0.0;

  // Query the KD-tree for photons within the specified radius
  std::vector<Photon> nearbyPhotons = photonTree.rangeSearch(center, radius);

  // Calculate the contribution of each nearby photon and accumulate it
  for (const Photon &photon : nearbyPhotons) {
    double distance = glm::length(photon.pos - center);
    // Calculate a weight based on the distance (might be worth experimenting
    // with weight function)
    double weight = 1.0 / (distance + 0.001); // Adjust the function as needed

    totalContribution += photon.color * weight;
    totalWeight += weight;
  }

  // Normalize the total contribution by the sum of weights to get the
  // weighted average
  if (totalWeight != 0.0) {
    totalContribution /= totalWeight;
  }

  return totalContribution;
}
