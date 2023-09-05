#pragma once
#include <iostream>
#include <vector>


class ColorRGB {
private:
	double R = 0.0;
	double G = 0.0;
	double B = 0.0;

public:
	ColorRGB() {};

	ColorRGB(double r, double g, double b): R{ std::min(std::max(r, 0.0), 255.0) }, 
											G{ std::min(std::max(g, 0.0), 255.0) }, 
											B{ std::min(std::max(b, 0.0), 255.0) } {}

	double getR() { return R; }

	double getG() { return G; }

	double getB() { return R; }

	void setR(double r) { R = r; }

	void setG(double g) { G = g; }

	void setB(double b) { B = b; }

	friend std::ostream& operator<<(std::ostream& os, const ColorRGB& c) {
		os << "[ " << c.R << ", " << c.G << ", " << c.B << " ]\n";
		return os;
	}

};

