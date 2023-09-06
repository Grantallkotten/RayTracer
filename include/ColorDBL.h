#pragma once
#include <iostream>
#include <vector>

// Beh�ver kanske �ndra s� f�rger �r mellan 0 och 1 f�r att det ska funka med programeringen
class ColorDBL {
private:
	double R = 0.0;
	double G = 0.0;
	double B = 0.0;

public:
	ColorDBL() {};

	ColorDBL(const double& r, const double& g, const double& b): R{ std::min(std::max(r, 0.0), 1.0) },
											G{ std::min(std::max(g, 0.0), 1.0) }, 
											B{ std::min(std::max(b, 0.0), 1.0) } {}

	double getR() { return R; }

	double getG() { return G; }

	double getB() { return R; }

	void setR(const double& r) { R = r; }

	void setG(const double& g) { G = g; }

	void setB(const double& b) { B = b; }

	friend std::ostream& operator<<(std::ostream& os, const ColorDBL& c) {
		os << "[ " << c.R * 255.0 << ", " << c.G * 255 << ", " << c.B * 255.0 << " ] / 255\n";
		return os;
	}

};
