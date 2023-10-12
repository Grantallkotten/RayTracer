#pragma once
#include <iostream>
#include <vector>
#include "ColorDBL.h"
#include "glm/glm.hpp"

enum MaterialProperty { diffusion, specularity, translucence, glossy, light };
class Material {
private:
    MaterialProperty property;
    ColorDBL color;

public:
    Material(MaterialProperty property = diffusion, ColorDBL color = ColorDBL(1.0, 0.0, 0.0)) :
        property{ property }, color{color} {
    
    }
    MaterialProperty getProperty() { return property; }

    ColorDBL getColor() const { return color; }
};

