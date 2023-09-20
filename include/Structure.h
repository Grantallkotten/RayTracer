#pragma once
#include "../include/glm/glm.hpp"
#include "../include/ColorDBL.h"
#include "../include/Ray.h"
#include "../include/Material.h"

class Structure {
private:
	  std::vector<Object* > objects;
  public:
	  void add(Object* o) {
		  objects.push_back(o);
	  }
	  const std::vector<Object* >& Objects() { return objects; }

};
