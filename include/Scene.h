#pragma once
#include <iostream>
#include <vector>
#include "Object.h"
#include "glm/glm.hpp"

class Scene {
private:
	std::vector<Object*> theScene;
public:
  Scene(std::vector<Object*> objects) : theScene{objects}{};
};
