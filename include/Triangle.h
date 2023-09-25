#pragma once
#include "Material.h"
#include "Object.h"

class Triangle : public Object {
private:
  glm::vec3 point0;
  glm::vec3 point1;
  glm::vec3 point2;
  glm::vec3 normal;
  Material material;

protected:
  glm::vec3 E1, E2;

public:
  Triangle(const glm::vec3 &p0 = glm::vec3(13.0f, 0.0f, 5.0f),
           const glm::vec3 &p1 = glm::vec3(10.0f, -6.0f, 5.0f),
           const glm::vec3 &p2 = glm::vec3(13.0f, 0.0f, -5.0f),
           const Material &m = Material(Material::diffusion,
                                        ColorDBL(1.0, 0.0, 0.0)))
      : point0{p0}, point1{p1}, point2{p2}, material{m}
  // Måste kolla så alla points lägger sig med högerhandsregeln
  {
    E1 = point1 - point0;
    E2 = point2 - point0;

    normal = glm::normalize(glm::cross(E1, E2));
  }

  glm::vec3 getNormal(glm::vec3 point = glm::vec3()) override { return normal; }

  Material getMaterial() override { return material; }

  bool Collision(Ray *ray, CollisionInfo& collisionInfo) override;

  glm::vec3 getP0() { return point0; }

  glm::vec3 getP1() { return point1; }

  glm::vec3 getP2() { return point2; }
};
