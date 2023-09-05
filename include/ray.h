#pragma once
#include <iostream>
#include <vector>
#include "../include/colorRGB.h"
#include "../include/glm/glm.hpp"

class Ray {
private:
	glm::vec3 orig; 
	glm::vec3 dir;
	Ray* surf = nullptr;
	Ray* prev = nullptr;
	Ray* next = nullptr;
	ColorRGB color;

public:
	Ray();

	ColorRGB getColor() { return color; }

	void rayColor() { std::cout << color; };
};

