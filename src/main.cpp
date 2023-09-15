// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#pragma once
#include <iostream>
#include "../include/ray.h"
#include "../include/ColorDBL.h"
#include "../include/Camera.h"
#include "../include/glm/glm.hpp"
#include "../include/Scene.h"
#include "../include/Triangle.h"



// https://www.youtube.com/watch?v=gfW1Fhd9u9Q&list=PLlrATfBNZ98edc5GshdBtREv5asFW3yXl
// https://raytracing.github.io/books/RayTracingInOneWeekend.html
// https://github.com/3DJakob/tncg15-ray-tracer/blob/main/TNCG15%20Ray%20Tracer/Classes/camera.h

int main()
{
    std::cout << "Hello World!\n";

    Triangle* myTriangle = new Triangle(glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(2.0f, -1.0f, 1.0f), glm::vec3(2.0f, 0.0f, 1.0f));

    Camera c = Camera(glm::vec3(-1.0f, 0.0f, 0.0f), 80);

    std::vector<Object*> myObjects;
    //myObjects.push_back(myTriangle);
    Scene myScene = Scene(myObjects, c);
    

    //c.writePPM();
}

