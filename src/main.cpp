// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#pragma once
#include <iostream>
#include "../include/ray.h"
#include "../include/colorRGB.h"
//#include "../include/vec3.h"
#include "../include/glm/glm.hpp"

// https://www.youtube.com/watch?v=gfW1Fhd9u9Q&list=PLlrATfBNZ98edc5GshdBtREv5asFW3yXl
// https://raytracing.github.io/books/RayTracingInOneWeekend.html

int main()
{
    std::cout << "Hello World!\n";
    
    ray myRay;
    myRay.test();
    
    glm::vec3 myVec1 = glm::vec3(1.f, 1.f, 1.f);
}


// To do
// *

