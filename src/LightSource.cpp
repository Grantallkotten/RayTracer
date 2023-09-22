#include "../include/LightSource.h"
#include "../include/Scene.h"
#include <random>
#define _PI 3.14159265358979323846

std::default_random_engine seed;
std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

double LightSource::CheckShadowRays(Scene *scene, Object *objectX,
                                    const glm::vec3 &x) {
  if (typeid(*objectX) == typeid(LightSource)) {
    return 1.0;
  }

  float sum = 0.0;
  int N = 50;
  float A = glm::length(E1) * glm::length(E2) /
            2; // @TODO Kolla så denna är tänkt rätt med punkter
  glm::vec3 Nx = objectX->getNormal(x); // @TODO fix getNormal for spheres

  for (int i = 1; i <= N; i++) {
    float s = ((float)rand() / (RAND_MAX));
    float t = ((float)rand() / (RAND_MAX));

    if (s + t > 1) {
      s = 1 - s;
      t = 1 - t;
    }

    glm::vec3 yi = getP0() + s * E1 + t * E2;
    glm::vec3 di = yi - x;
    glm::vec3 Ny = getNormal(yi);
    // std::cout << "\n\n\n";
    // std::cout << "d_i: " << di.x << " " << di.y << " " << di.z << "\n\n\n";
    //  @TODO Check if no collission V(x,y_i) and do it right
    if (!Ray(x, di).ShadowRay(scene)) {
      continue;
    }

    float cosX = glm::dot(Ny, di / glm::length(di));
    float cosY = -glm::dot(Nx, di / glm::length(di));

    sum += std::max(0.0f, (cosX * cosY) / (glm::length(di) * glm::length(di)));
  }
  float BRDF = 1.0f / _PI;

  return (float)(A * BRDF * radiance / N * sum);
}
