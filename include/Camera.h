#pragma once
#include <iostream>
#include <vector>
#include "../include/ColorDBL.h"
#include "../include/glm/glm.hpp"
#include "../include/Pixel.h"


class Camera {
private:
	std::vector<std::vector<Pixel>> CameraPlane;

public:
	Camera(const float& width, const float& height) : 
		CameraPlane{ std::vector<std::vector<Pixel>>(width,std::vector<Pixel>(height, Pixel()))} 
	{};

	/*
	1. Loop through all pixels.
	2. Shoot a ray through each pixel.
	3. Compute its intersection point with the scene boundary.
	4. Give the color of that rectangle or triangle to the pixel.
	5. After the loop over all pixels finished, you find the largest
	   double precision value in all of the pixels and you divide the r,
	g, b values of all pixels by this maximum value.
	6. You map the double values to the RGB range 0-255 and
	   create an image with these values.
	*/
};

