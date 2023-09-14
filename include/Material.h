#pragma once
#include <iostream>
#include <vector>
#include "ColorDBL.h"
#include "glm/glm.hpp"

class Material {
private:
    double diffusion;
    double specularity;
    double translucence;
    ColorDBL color;

public:

    Material(double diffusion, double specularity, double translucence, ColorDBL color) : 
        diffusion{ diffusion }, specularity{ specularity }, translucence{ translucence }, color{ color } {}
	
    double getDiffusion() { return diffusion; }

    double getSpecularity() { return specularity; }

    double getTranslucence() { return translucence; }

    ColorDBL getColor() { return color;  }



};

