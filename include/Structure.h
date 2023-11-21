#pragma once
#include "ColorDBL.h"
#include "Material.h"
#include "Ray.h"
#include <glm/glm.hpp>

class Structure {
private:
  std::vector<Object *> objects;

public:
  void add(Object *o) { objects.push_back(o); }
  const std::vector<Object *> &Objects() { return objects; }
};
