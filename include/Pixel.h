#pragma once
#include <iostream>
#include <vector>
#include <string>// To write a pixel into ppm format
#include "../include/ColorDBL.h"
#include "../include/glm/glm.hpp"

class Pixel {
private:
	ColorDBL color;
public:	
	Pixel() : color{ ColorDBL(0.0, 0.0, 0.0)} {}

	ColorDBL getColor() const { return color; }

	void setColor(const ColorDBL& c) { color = c; }

	void operator+=(const ColorDBL& c) { color += c; }

	friend std::ostream& operator<<(std::ostream& os, const Pixel& p) {
		os << p.color;
		return os;
	}
};

