#pragma once
#include <iostream>
#include <vector>
#include <fstream>// Write a file
#include "../include/ColorDBL.h"
#include "../include/glm/glm.hpp"
#include "../include/Pixel.h"
#include "../include/Ray.h"



class Camera {
private:
	std::vector<std::vector<Pixel>> CameraPlane;
	float pixelLength;
	int size;
	const int maxColorValue = 255;
	glm::vec3 positionCamera;
	glm::vec3 positionPlaneCenter;
public:

	Camera(const glm::vec3& p = glm::vec3(-1.0f, 0.0f, 0.0f), const int& s = 800) :
		CameraPlane{ std::vector<std::vector<Pixel>>(s,std::vector<Pixel>(s)) }, size{ s }, positionCamera{ p }, positionPlaneCenter{ p + glm::vec3(1.0f, 0.0f, 0.0f), }, pixelLength{2/float(s-1)}
	{
	};

	void writePPM();

	void castRays(Scene* scene);

	void RenderRangeOfColums(Scene* scene, int start_row, int end_row);

	void Render(Scene* scene);

};

