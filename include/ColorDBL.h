#pragma once
#include <iostream>
#include <vector>

// Behöver kanske ändra så färger är mellan 0 och 1 för att det ska funka med programeringen
class ColorDBL {
private:
	float R = 0.0f;
	float G = 0.0f;
	float B = 0.0f;

public:
	ColorDBL() {};

	ColorDBL(const float& r, const float& g, const float& b): R{ std::min(std::max(r, 0.0f), 1.0f) },
											G{ std::min(std::max(g, 0.0f), 1.0f) }, 
											B{ std::min(std::max(b, 0.0f), 1.0f) } {}

	float getR() { return R; }

	float getG() { return G; }

	float getB() { return R; }

	void setR(const float& r) { R = r; }

	void setG(const float& g) { G = g; }

	void setB(const float& b) { B = b; }

	friend std::ostream& operator<<(std::ostream& os, const ColorDBL& c) {
		os << "[ " << c.R * 255.0 << ", " << c.G * 255 << ", " << c.B * 255.0 << " ] / 255\n";
		return os;
	}

};

