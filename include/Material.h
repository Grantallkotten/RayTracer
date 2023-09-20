#pragma once
#include <iostream>
#include <vector>
#include "ColorDBL.h"
#include "glm/glm.hpp"

class Material {
public:
    enum MaterialProperty { diffusion, specularity , translucence };
private:
    MaterialProperty property;
    ColorDBL color;

public:

    Material(MaterialProperty property = diffusion, ColorDBL color = ColorDBL(1.0, 0.0, 0.0)) :
        property{ property }, color{color} {
    
    }
	
    double getDiffusion() { return diffusion; }

    double getSpecularity() { return specularity; }

    double getTranslucence() { return translucence; }

    ColorDBL getColor() { return color;  }


};

