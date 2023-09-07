#pragma once
#include <iostream>
#include <vector>
#include <fstream>// Write a file
#include "../include/ColorDBL.h"
#include "../include/glm/glm.hpp"
#include "../include/Pixel.h"


class Camera {
private:
	std::vector<std::vector<Pixel>> CameraPlane;
	int width;
	int height;
	const int maxColorValue = 255;
	glm::vec3 position;

public:

	Camera(const int& w  = 800, const int& h = 800) : 
		CameraPlane{ std::vector<std::vector<Pixel>>(w,std::vector<Pixel>(h)) }, width{ w }, height{h}
	{};


	void writePPM();


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

