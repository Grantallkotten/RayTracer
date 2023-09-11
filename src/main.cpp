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
/*TODO_BIG
     1. Get the plane up with the right dimensions
     2. Make sure all pixels in the plane are defined
     3. Calculate direction via end and start vec3 in the Ray class
     4. Implement the polygon class --> the triangle class which is a subclass
     5. Make some kind of collision detector for a ray (has many steps)
     6. Ad a traingel to the sceen via a vertex table
     7. Send a ray through all pixels into the room
     8. We collsion give pixel color
     9. Do 5. - 7. for all pixels
     10. Create ppm
*/
//@TODO Add a intersection function to the super class for triangel, this should return the point the ray intersects the rurface
int main()
{
    std::cout << "Hello World!\n";
    
    ColorDBL myColor(100.0/255.0, -220.0/255.0, 1000.0/255.0);
    std::cout << myColor;

    Camera c = Camera(glm::vec3(-1.0f, 0.0f, 0.0f), 80);
    
    c.castRayes();
    //c.writePPM();
}

