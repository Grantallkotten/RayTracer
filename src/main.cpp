// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#pragma once
#include <iostream>
#include "../include/ray.h"
#include "../include/ColorDBL.h"
#include "../include/Camera.h"
#include "../include/glm/glm.hpp"

// https://www.youtube.com/watch?v=gfW1Fhd9u9Q&list=PLlrATfBNZ98edc5GshdBtREv5asFW3yXl
// https://raytracing.github.io/books/RayTracingInOneWeekend.html
// https://github.com/3DJakob/tncg15-ray-tracer/blob/main/TNCG15%20Ray%20Tracer/Classes/camera.h

int main()
{
    std::cout << "Hello World!\n";
    
    ColorDBL myColor(100.0/255.0, -220.0/255.0, 1000.0/255.0);
    std::cout << myColor;

    Camera c;

    c.writePPM();
}


// To do
// *

