#pragma once
#include "../include/Camera.h"

void Camera::castRays(Scene* scene) {
    glm::vec3 pixelPosition = positionCamera + glm::vec3(1.0f, -1.0f, -1.0f);

    for (std::vector<Pixel>& widthVec : CameraPlane) {
        pixelPosition.z = -1.0f;
        for (Pixel& p : widthVec) {

            Ray r = Ray(positionCamera, glm::normalize(pixelPosition - positionCamera));
            p.setColor(r.castRay(scene, nullptr, 1.0));

            pixelPosition.z += pixelLength;
        }
        pixelPosition.y += pixelLength;
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



