#pragma once
#include "Object.h"
#include "ColorDBL.h"
#include "glm/glm.hpp"
#include "Camera.h"

class Scene {
private:
	std::vector<Object*> theScene;
	Camera camera;
public:

  const ColorDBL SKYBOXCOLOR = ColorDBL(0.21, 0.32, 0.36);

	Scene(std::vector<Object*> o, Camera c) : theScene{ o }, camera{ c } {
		camera.castRays(this);
		camera.writePPM();
	};

  std::vector<Object*> getObjects() { return theScene; }
};
