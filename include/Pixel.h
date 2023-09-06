#pragma once
#include <iostream>
#include <vector>
#include "../include/ColorDBL.h"
#include "../include/glm/glm.hpp"

class Pixel {
private:
	const float length = 0.0025f;
	ColorDBL color;
public:
	float getLength() { return length; }
	
	ColorDBL getColor() { return color; }

	void setColor(const ColorDBL& c) { color = c; }

};

