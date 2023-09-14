#pragma once
#include "../include/Camera.h"

void Camera::castRays(Scene* scene) {
    glm::vec3 pixelPosition = positionCamera + glm::vec3(1.0f, -1.0f, -1.0f);

    for (std::vector<Pixel>& widthVec : CameraPlane) {
        pixelPosition.z = -1.0f;
        for (Pixel& p : widthVec) {

            //@TODO Skjut ray som ger tillbaka en ray vars färg man ger till pixeln p
                //Ray(const glm::vec3& origin, const glm::vec3& direction) : orig(origin), dir(direction) {}

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

            #if 1
            /*@TODO
            1. Loop through all pixels.
            2. Shoot a ray through each pixel.
            3. Compute its intersection point with the scene boundary.
            4. Give the color of that rectangle or triangle to the pixel.
            5. After the loop over all pixels finished, you find the largest double precision value in all of the pixels and you divide the r,
            g, b values of all pixels by this maximum value.
            6. You map the double values to the RGB range 0-255 and create an image with these values.

            When looking for hits, loop thrugh all possible objects
            A hit van be confirmed by comparing normal an direction dir.dot(N) < 0 --> possible hit

            Sist hitta max rgb färgen bland pixlarna och dela sen alla pixlar på det värdet för att sen köra * 255
            maybe devide by sqrt(max)
            Möller finns i wikipedia färdigimplementerad i C++
            */
            outFile << p;// Write the pixel data to the file
            #endif  

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



