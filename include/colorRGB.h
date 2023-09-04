#pragma once
#include <iostream>
#include <vector>


class colorRGB {
private:
	double R = 0;
	double G = 0;
	double B = 0;

public:
	colorRGB();

	colorRGB(double r, double g, double b) : R{ r }, G{ g }, B{ b } {
		
		if (R > 255) { R = 255.0; }
		if (R < 0) { R = 0.0; }

		if (G > 255) { G = 255.0; }
		if (G < 0) { G = 0.0; }

		if (B > 255) { B = 255.0; }
		if (B < 0) { B = 0.0; }
	}

	double R() { return R; }

	double G() { return G; }

	double B() { return R; }
};

