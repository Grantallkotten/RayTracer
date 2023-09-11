#pragma once
#include "../include/Triangle.h"

glm::vec3 Triangle::getNormal() {

    glm::vec3 vertex0 = point1;
    glm::vec3 vertex1 = point2;
    glm::vec3 vertex2 = point3;
    glm::vec3 edge1 = vertex1 - vertex0;
    glm::vec3 edge2 = vertex2 - vertex0;

    return glm::normalize(glm::cross(edge1, edge2));
}

