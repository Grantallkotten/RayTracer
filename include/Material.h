#pragma once
#include <iostream>
#include <vector>
#include "ColorDBL.h"
#include "glm/glm.hpp"

class Material {
public:
    enum MaterialProperty { diffusion, specularity , translucence, glossy, light};
private:
    MaterialProperty property;
    ColorDBL color;

public:
    Material(MaterialProperty property = diffusion, ColorDBL color = ColorDBL(1.0, 0.0, 0.0)) :
        property{ property }, color{color} {
    
    }
    MaterialProperty getMaterialProperty() { return property; }

    ColorDBL getColor() const { return color;  }


};

