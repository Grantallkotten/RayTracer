#pragma once

#include "../include/glm/glm.hpp"
#include "../include/ColorDBL.h"

class Surface {
  private:
  public:
  Surface() {};
  virtual glm::vec3 Normal();
  virtual ColorDBL Color();
};
