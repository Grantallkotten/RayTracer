#pragma once
#include "../include/ColorDBL.h"
#include "../include/Pixel.h"
#include "../include/Ray.h"
#include "../include/glm/glm.hpp"
#include <fstream> // Write a file
#include <iostream>
#include <vector>

class Camera {
private:
  std::vector<std::vector<Pixel>> CameraPlane;
  float pixelLength;
  int size;
  int raysPerPixel = 1;
  const int maxColorValue = 255;
  glm::vec3 positionCamera;
  glm::vec3 positionPlaneCenter;

  float percentDone = 0.0f;
  const int BAR_WIDTH = 20;

public:
  Camera(const glm::vec3 &p = glm::vec3(-1.0f, 0.0f, 0.0f), const int & s = 800)
      : CameraPlane{std::vector<std::vector<Pixel>>(s, std::vector<Pixel>(s))},
        pixelLength{2 / float(s - 1)}, size{s}, positionCamera{p},
        positionPlaneCenter{
            p + glm::vec3(1.0f, 0.0f, 0.0f),
        } {};

  void writePPM();

  void castRays(Scene *scene);

  void renderRangeOfColums(Scene *scene, int start_row, int end_row);

  void render(Scene *scene);

  void progressBar(float percent);
};
