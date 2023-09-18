#pragma once
#include "../include/Camera.h"
#include <thread>
#include <time.h>

void Camera::castRays(Scene* scene) {
    std::cout << "Casting rays...\n";
    glm::vec3 pixelPosition = positionCamera + glm::vec3(1.0f, 1.0f, 1.0f);


    for (std::vector<Pixel>& widthVec : CameraPlane) {
        pixelPosition.y = 1.0f;
        for (Pixel& p : widthVec) {

            Ray r = Ray(positionCamera, glm::normalize(pixelPosition - positionCamera));
            p.setColor(r.castRay(scene, nullptr, 1.0));
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
        pixelPosition.z  -= pixelLength;
    }
}

void Camera::RenderRangeOfColums(Scene* scene, int start_colum, int end_colum) {
    glm::vec3 pixelPosition = positionCamera + glm::vec3(1.0f, 1.0f, 1.0f);
    pixelPosition.z -= pixelLength * start_colum;
    for (int colum = start_colum; colum < end_colum; colum++) {
        pixelPosition.y = 1.0f;
        for (Pixel& p : CameraPlane[colum]) {
            Ray r = Ray(positionCamera, glm::normalize(pixelPosition - positionCamera));
            p.setColor(r.castRay(scene, nullptr, 1.0));
            pixelPosition.y -= pixelLength;
        }
        pixelPosition.z -= pixelLength;
    }
}

void Camera::Render(Scene* scene) {
    unsigned int num_threads = std::thread::hardware_concurrency();
    std::cout << "Rendering using " << num_threads << " threads \n";
    std::vector<std::thread> threads(num_threads);
    int colums_per_thread = CameraPlane.size() / num_threads;
    int start_colum = 0;
    for (int i = 0; i < num_threads; i++) {
        threads[i] = std::thread([=]() {
            RenderRangeOfColums(scene, i * colums_per_thread, i == num_threads - 1 ? (i + 1) * colums_per_thread : CameraPlane.size());
            });
    }
    for (int i = 0; i < num_threads; i++) {
        threads[i].join();
    }
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

    int counter = 0;

    for (const std::vector<Pixel>& widthVec : CameraPlane) {
        counter = 0;
        for (const Pixel& p : widthVec) {

            outFile << p;// Write the pixel data to the file

            #if 0
            // PPM file test code
            // ========================================================
            int red = 25;
            int green = 100;
            int blue = counter * maxColorValue / size;
            counter++;

            outFile << red << " " << green << " " << blue << "\n";
            // ========================================================
            #endif
        }
    }

    outFile.close();
    std::cout << "PPM image generated successfully!" << std::endl;

}



