#pragma once
#include <iostream>
#include <vector>

// Behöver kanske ändra så färger är mellan 0 och 1 för att det ska funka med programeringen
class ColorDBL {
private:
	double R = 0.0;
	double G = 0.0;
	double B = 0.0;

public:
	ColorDBL() {};

	ColorDBL(double d) : R{ std::min(std::max(d, 0.0), 1.0) },
		G{ std::min(std::max(d, 0.0), 1.0) },
		B{ std::min(std::max(d, 0.0), 1.0) } {}


	ColorDBL(double r, double g, double b): R{ std::min(std::max(r, 0.0), 1.0) },
											G{ std::min(std::max(g, 0.0), 1.0) }, 
											B{ std::min(std::max(b, 0.0), 1.0) } {}

	double getR() { return R; }

	double getG() { return G; }

	double getB() { return R; }

	void setR(const double& r) { R = r; }

	void setG(const double& g) { G = g; }

	void setB(const double& b) { B = b; }

	void operator*=(const float& s) {
		R = std::min(1.0, R*(double)s);
		G = std::min(1.0, G*(double)s);
		B = std::min(1.0, B*(double)s);

	}

	friend void operator*=(ColorDBL& c1, const ColorDBL& c2) {
		c1.R *= std::min(c2.R,1.0);
		c1.G *= std::min(c2.G,1.0);
		c1.B *= std::min(c2.B,1.0);
	}

	friend void operator+=(ColorDBL& c1, const ColorDBL& c2) {
		c1.R += std::min(c2.R, 1.0);
		c1.G += std::min(c2.G, 1.0);
		c1.B += std::min(c2.B, 1.0);
	}

	friend void operator/=(ColorDBL& c1,const double& d) {
		c1.R /= d;
		c1.G /= d;
		c1.B /= d;
	}

	ColorDBL friend operator+(const ColorDBL& c1, const ColorDBL& c2) {
		return ColorDBL(c1.R + c2.R, c1.G + c2.G, c1.B + c2.B);
	}

	ColorDBL friend operator*(const ColorDBL& c1, const ColorDBL& c2) {
		return ColorDBL(c1.R * c2.R, c1.G * c2.G, c1.B * c2.B);
	}

	ColorDBL operator*(const double& d) {
		return ColorDBL(R *= d, G *= d, B *= d);
	}

	friend bool operator==(const ColorDBL& c1, const ColorDBL& c2) {
		if (c1.R == c2.R && c1.G == c2.G && c1.B == c2.B) {
			return true;
		}
		return false;
	}

	friend std::ostream& operator<<(std::ostream& os, const ColorDBL& c) {
		os << c.R * 255.0 << " " << c.G * 255 << " " << c.B * 255.0 << "\n";
		return os;
	}

};

