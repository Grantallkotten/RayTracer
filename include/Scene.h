#pragma once
#include "Camera.h"
#include "ColorDBL.h"
#include "LightSource.h"
#include "Object.h"
#include "Tetrahedron.h"
#include "Sphere.h"
#include "glm/glm.hpp"

class Scene {
private:
  Camera camera;

  // Draw an image and call all corners "pointX", then you can easy creat a room
  // in Objects
  std::vector<glm::vec3> points{
      glm::vec3(0.0f, 6.0f, 5.0f),   // p0
      glm::vec3(10.0f, 6.0f, 5.0f),  // p1
      glm::vec3(13.0f, 0.0f, 5.0f),  // p2
      glm::vec3(10.0f, -6.0f, 5.0f), // p3
      glm::vec3(0.0f, -6.0f, 5.0f),  // p4
      glm::vec3(-3.0f, 0.0f, 5.0f),  // p5

      glm::vec3(0.0f, 6.0f, -5.0f),   // p6
      glm::vec3(10.0f, 6.0f, -5.0f),  // p7
      glm::vec3(13.0f, 0.0f, -5.0f),  // p8
      glm::vec3(10.0f, -6.0f, -5.0f), // p9
      glm::vec3(0.0f, -6.0f, -5.0f),  // p10
      glm::vec3(-3.0f, 0.0f, -5.0f),  // p11
  };

public:
  std::vector<Object *> Objects;

  std::vector<LightSource *> LightSources;

  const ColorDBL SKYBOXCOLOR = ColorDBL(0.21, 0.32, 0.56);

  Scene(Camera c = Camera(glm::vec3(-1.0f, 0.0f, 0.0f), 360),
        std::vector<Object *> o = std::vector<Object *>())
      : camera{c}, Objects{o} {
    standardScene();
    camera.render(this);
    camera.writePPM();
  };

  void add(Structure s) {
    auto objs = s.Objects();
    for (unsigned long i = 0; i < objs.size(); i++) {
      Objects.push_back(objs[i]);
    }
  }

  void standardScene() {
    add(Tetrahedron(glm::vec3(8.0f, -1.0f, -1.0f), 2.0f, 4.0f));

    Objects.push_back(new Sphere(glm::vec3(8.0f, 3.0f, -2.0f), 2.0f));

    // Wall 1
    Objects.push_back(
        new Triangle(points[1], points[0], points[7],
                     Material(Material::diffusion, ColorDBL(0.5, 0.0, 0.0))));
    Objects.push_back(
        new Triangle(points[0], points[6], points[7],
                     Material(Material::diffusion, ColorDBL(0.5, 0.0, 0.0))));

    // Wall 2
    Objects.push_back(
        new Triangle(points[1], points[7], points[2],
                     Material(Material::diffusion, ColorDBL(0.0, 0.5, 0.1))));
    Objects.push_back(
        new Triangle(points[2], points[7], points[8],
                     Material(Material::diffusion, ColorDBL(0.0, 0.5, 0.1))));

    // Wall 3
    Objects.push_back(
        new Triangle(points[2], points[8], points[3],
                     Material(Material::diffusion, ColorDBL(0.0, 0.0, 0.5))));
    Objects.push_back(
        new Triangle(points[3], points[8], points[9],
                     Material(Material::diffusion, ColorDBL(0.0, 0.0, 0.5))));

    // Roof 1
    Objects.push_back(
        new Triangle(points[1], points[2], points[3],
                     Material(Material::diffusion, ColorDBL(0.1, 0.0, 0.2))));

    // Wall 4
    Objects.push_back(
        new Triangle(points[3], points[9], points[4],
                     Material(Material::diffusion, ColorDBL(0.5, 0.0, 0.3))));
    Objects.push_back(
        new Triangle(points[4], points[9], points[10],
                     Material(Material::diffusion, ColorDBL(0.5, 0.0, 0.3))));

    // Roof 2
    Objects.push_back(
        new Triangle(points[0], points[1], points[4],
                     Material(Material::diffusion, ColorDBL(0.1, 0.0, 0.2))));
    Objects.push_back(
        new Triangle(points[1], points[3], points[4],
                     Material(Material::diffusion, ColorDBL(0.1, 0.0, 0.2))));

    // Roof 3
    Objects.push_back(
        new Triangle(points[10], points[4], points[5],
                     Material(Material::diffusion, ColorDBL(0.1, 0.0, 0.2))));

    // Wall 5
    Objects.push_back(
        new Triangle(points[4], points[10], points[5],
                     Material(Material::diffusion, ColorDBL(0.0, 0.0, 0.5))));
    Objects.push_back(
        new Triangle(points[5], points[10], points[11],
                     Material(Material::diffusion, ColorDBL(0.0, 0.0, 0.5))));

    // Wall 6
    Objects.push_back(
        new Triangle(points[0], points[5], points[11],
                     Material(Material::diffusion, ColorDBL(0.0, 0.8, 0.2))));
    Objects.push_back(
        new Triangle(points[0], points[11], points[6],
                     Material(Material::diffusion, ColorDBL(0.0, 0.8, 0.2))));

    // Floor 1
    Objects.push_back(
        new Triangle(points[7], points[9], points[8],
                     Material(Material::diffusion, ColorDBL(0.2, 0.2, 0.4))));

    // Floor 2
    Objects.push_back(
        new Triangle(points[7], points[10], points[9],
                     Material(Material::diffusion, ColorDBL(0.2, 0.2, 0.4))));
    Objects.push_back(
        new Triangle(points[7], points[6], points[10],
                     Material(Material::diffusion, ColorDBL(0.2, 0.2, 0.4))));

    // Floor 3
    Objects.push_back(
        new Triangle(points[6], points[11], points[10],
                     Material(Material::diffusion, ColorDBL(0.2, 0.2, 0.4))));

    // Triforce
    // Objects.push_back(new Triangle(glm::vec3(10.0f, 4.8f, 1.0f),
    // glm::vec3(10.0f, 3.8f, 0.0f), glm::vec3(10.0f, 5.8f, 0.0f),
    // Material(Material::diffusion, ColorDBL(0.8, 0.8, 0.0))));
    // Objects.push_back(new Triangle(glm::vec3(10.0f, 2.8f, 1.0f),
    // glm::vec3(10.0f, 1.8f, 0.0f), glm::vec3(10.0f, 3.8f, 0.0f),
    // Material(Material::diffusion, ColorDBL(0.8, 0.8, 0.0))));
    // Objects.push_back(new Triangle(glm::vec3(10.0f, 3.8f, 2.0f),
    // glm::vec3(10.0f, 2.8f, 1.0f), glm::vec3(10.0f, 4.8f, 1.0f),
    // Material(Material::diffusion, ColorDBL(0.8, 0.8, 0.0))));


    // Roof lamp
    LightSources.push_back(new LightSource(
        glm::vec3(5.0f, 0.5f, 4.9f), glm::vec3(9.0f, 0.5f, 4.9f),
        glm::vec3(9.0f, -0.5f, 4.9f),
        Material(Material::diffusion, ColorDBL(0.8, 0.8, 0.9))));
    LightSources.push_back(new LightSource(
        glm::vec3(5.0f, -0.5f, 4.9f), glm::vec3(5.0f, 0.5f, 4.9f),
        glm::vec3(9.0f, -0.5f, 4.9f),
        Material(Material::diffusion, ColorDBL(0.8, 0.8, 0.9))));

    Objects.push_back(new LightSource(
        glm::vec3(5.0f, 0.5f, 4.9f), glm::vec3(9.0f, 0.5f, 4.9f),
        glm::vec3(9.0f, -0.5f, 4.9f),
        Material(Material::diffusion, ColorDBL(1.0, 1.0, 1.0))));
    Objects.push_back(new LightSource(
        glm::vec3(5.0f, -0.5f, 4.9f), glm::vec3(5.0f, 0.5f, 4.9f),
        glm::vec3(9.0f, -0.5f, 4.9f),
        Material(Material::diffusion, ColorDBL(1.0, 1.0, 1.0))));
  }
};
