#pragma once
#include "ColorDBL.h"
#include "Pixel.h"
#include "Ray.h"
#include <fstream> // Write a file
#include <glm/glm.hpp>
#include <iomanip>
#include <iostream>
#include <vector>

class Camera {
private:
  std::vector<std::vector<Pixel>> CameraPlane;
  float pixelLength;
  int size;
  int raysPerPixel = 10;
  const int maxColorValue = 255;
  glm::vec3 positionCamera;
  glm::vec3 positionPlaneCenter;

  float percentDone = 0.0f;
  const int BAR_WIDTH = 20;

public:
  Camera(const glm::vec3 &p = glm::vec3(-1.0f, 0.0f, 0.0f), const int &s = 800)
      : CameraPlane{std::vector<std::vector<Pixel>>(s, std::vector<Pixel>(s))},
        pixelLength{2 / float(s - 1)}, size{s}, positionCamera{p},
        positionPlaneCenter{
            p + glm::vec3(1.0f, 0.0f, 0.0f),
        } {};

  void writePPM();

  void castRays(Scene *scene, KDTree<Photon> photons);

  void renderRangeOfColums(Scene *scene, KDTree<Photon> photons,
                           unsigned int rays_per_pixel, float death_probability,
                           int start_row, int end_row, int threads_done,
                           int num_threads);

  void render(Scene *scene, KDTree<Photon> photons, unsigned int rays_per_pixel,
              float death_probability);

  void progressBar(float percent);
};
