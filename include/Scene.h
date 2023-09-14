#pragma once
#include "Object.h"
<<<<<<< Updated upstream
#include "glm/glm.hpp"
=======
#include "Camera.h"
>>>>>>> Stashed changes

class Scene {
private:
	std::vector<Object*> theScene;
public:
<<<<<<< Updated upstream
  Scene(std::vector<Object*> objects) : theScene{objects}{};
=======

	Scene(std::vector<Object*> o, Camera c) : theScene{ o }, camera{ c } {
		camera.castRays(this);
		camera.writePPM();
	};

  const ColorDBL SKYBOXCOLOR = ColorDBL(0.21, 0.32, 0.36);

>>>>>>> Stashed changes

  std::vector<Object*> getObjects() { return theScene; }
};
