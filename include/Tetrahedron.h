#pragma once
#include "Material.h"
#include "Structure.h"
#include "Triangle.h"
#include <glm/glm.hpp>

class Tetrahedron : public Structure {
private:
  glm::vec3 point0, point1, point2, point3;
  Material material;

public:
  /// <summary>
  ///
  /// </summary>
  /// <param name="p0"></param>
  /// <param name="p1"></param>
  /// <param name="p2"></param>
  /// <param name="p3">Top point</param>
  /// <param name="m">Material</param>
  Tetrahedron(const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2,
              const glm::vec3 &p3,
              const Material &m = Material(diffusion, ColorDBL(0.4, 0.0, 0.2)))
      : point0{p0}, point1{p1}, point2{p2}, point3{p3}, material{m} {
    add(new Triangle(p0, p1, p2, m));
    add(new Triangle(p0, p2, p3, m));
    add(new Triangle(p1, p3, p2, m));
    add(new Triangle(p0, p3, p1, m));
  }

  Tetrahedron(const glm::vec3 &center, float width = 0.5f, float height = 1.0f,
              const Material &m = Material(diffusion,
                                           ColorDBL(0.4, 0.0, 0.2))) {
    // Calculate half-width and half-height
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    // Calculate the vertices
    point0 = glm::vec3(center.x - halfWidth, center.y,
                       center.z - halfHeight); // Back
    point1 = glm::vec3(center.x + halfWidth, center.y + halfWidth,
                       center.z - halfHeight); // Left
    point2 = glm::vec3(center.x + halfWidth, center.y - halfWidth,
                       center.z - halfHeight);                     // Right
    point3 = glm::vec3(center.x, center.y, center.z + halfHeight); // Top
    add(new Triangle(point0, point1, point2, m));                  // bottom
    add(new Triangle(point0, point2, point3, m));                  // right
    add(new Triangle(point1, point3, point2, m));                  // back
    add(new Triangle(point0, point3, point1, m));                  // left
  }

  glm::vec3 getP0() { return point0; }

  glm::vec3 getP1() { return point1; }

  glm::vec3 getP2() { return point2; }

  glm::vec3 getP3() { return point3; }
};
