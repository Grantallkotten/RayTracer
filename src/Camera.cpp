#pragma once
#include "../include/Camera.h"

void Camera::writePPM() {
    std::cout << "Generating PPM image..." << std::endl;

    std::ofstream outFile("../output.ppm");

    if (!outFile) {
        std::cout << "Failed to open output.ppm" << std::endl;
        return;
    }

    outFile << "P3\n"; // P3 indicates ASCII PPM format
    outFile << width << " " << height << "\n";
    outFile << maxColorValue << "\n";

    int counter = 0;

    for (const std::vector<Pixel>& widthVec : CameraPlane) {
        counter = 0;
        for (const Pixel& p : widthVec) {;
            #if 0
            outFile << p;// Write the pixel data to the file
            #endif  
            #if 1
            int red = 25;
            int green = 100;
            int blue = counter * maxColorValue / width;
            counter++;

            outFile << red << " " << green << " " << blue << "\n";
            #endif
        }
    }

    outFile.close();
    std::cout << "PPM image generated successfully!" << std::endl;

}



