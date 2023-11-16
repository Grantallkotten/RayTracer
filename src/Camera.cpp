#include "../include/Camera.h"
#include <thread>
#include <time.h>

void Camera::castRays(Scene *scene, KDTree<Photon> photons) {
  std::cout << "Casting rays...\n";
  glm::vec3 pixelPosition = positionCamera + glm::vec3(1.0f, 1.0f, 1.0f);

  for (std::vector<Pixel> &widthVec : CameraPlane) {
    pixelPosition.y = 1.0f;
    for (Pixel &p : widthVec) {

      Ray r =
          Ray(positionCamera, glm::normalize(pixelPosition - positionCamera));
      p.setColor(r.castRay(scene, photons, 1.0));
#if 0
            if (pixelPosition.z > 0.9) {
                std::cout << "positive z-axis direction black\n";
                p.setColor(ColorDBL(0.0, 0.0, 0.0));
            }
            if (pixelPosition.y > 0.9) {
                std::cout << "positive y-axis direction white\n";
                p.setColor(ColorDBL(1.0, 1.0, 1.0));
            }
#endif
      pixelPosition.y -= pixelLength;
    }
    pixelPosition.z -= pixelLength;
  }
}

void Camera::renderRangeOfColums(Scene *scene, KDTree<Photon> photons,
                                 unsigned int rays_per_pixel,
                                 float death_probability, int start_colum,
                                 int end_colum, int threads_done,
                                 int num_threads) {
  glm::vec3 pixelPosition = positionCamera + glm::vec3(1.0f, 1.0f, 1.0f);
  pixelPosition.z -= pixelLength * start_colum;
  for (int colum = start_colum; colum < end_colum; colum++) {
    pixelPosition.y = 1.0f;
    for (Pixel &p : CameraPlane[colum]) {
      Ray r =
          Ray(positionCamera, glm::normalize(pixelPosition - positionCamera));
      ColorDBL c(0.0, 0.0, 0.0);
      for (unsigned int i = 0; i < rays_per_pixel; i++) {
        c += (r.castRay(scene, photons, death_probability));
      }
      c /= raysPerPixel;
      p.setColor(c);
      pixelPosition.y -= pixelLength;
    }
    pixelPosition.z -= pixelLength;
  }

  std::cout << std::setw(5) << std::fixed << std::setprecision(1)
            << (1.0 - (double)threads_done / (double)num_threads) * 100.0
            << " %\n";
}

void Camera::render(Scene *scene, KDTree<Photon> photons,
                    unsigned int rays_per_pixel, float death_probability) {
  unsigned int num_threads = std::thread::hardware_concurrency();
  std::cout << "Rendering using " << num_threads << " threads...\n";
  std::cout << std::setw(5) << std::fixed << std::setprecision(1) << 0.0
            << " %\n";
  std::vector<std::thread> threads(num_threads);
  int colums_per_thread = CameraPlane.size() / num_threads;
  for (unsigned int i = 0; i < num_threads; i++) {
    threads[i] = std::thread([=]() {
      renderRangeOfColums(scene, photons, rays_per_pixel, death_probability,
                          i * colums_per_thread,
                          i == num_threads - 1 ? (i + 1) * colums_per_thread
                                               : CameraPlane.size(),
                          i, num_threads);
    });
  }
  for (unsigned int i = 0; i < num_threads; i++) {
    threads[i].join();
  }
  std::cout << "Rendering complete!\n";
}

void Camera::writePPM() {
  std::cout << "Generating PPM image..." << std::endl;

  std::ofstream outFile("../outPPM/output.ppm");

  if (!outFile) {
    std::cout << "Failed to open output.ppm" << std::endl;
    return;
  }

  outFile << "P3\n"; // P3 indicates ASCII PPM format
  outFile << size << " " << size << "\n";
  outFile << maxColorValue << "\n";

  for (const std::vector<Pixel> &widthVec : CameraPlane) {
    for (const Pixel &p : widthVec) {
      // percentDone += 1.0;
      // progressBar(percentDone/(size*size));
      outFile << p; // Write the pixel data to the file
    }
  }

  outFile.close();
  std::cout << "PPM image generated successfully!" << std::endl;
}

// Display a progress bar over the rendered/saved image
// Code from
// https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
void Camera::progressBar(float percent) {
  std::cout << "[";
  int pos = (int)(BAR_WIDTH * percent);
  for (int i = 0; i < BAR_WIDTH; ++i) {
    if (i <= pos)
      std::cout << "=";
    else
      std::cout << " ";
  }
  std::cout << "] " << int(percent * 100.0f + 0.5f)
            << " %\r"; // +0.5 for round-off error
  std::cout.flush();
}
