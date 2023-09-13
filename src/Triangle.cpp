#pragma once
#include "../include/Triangle.h"

void Triangle::calcNormal() {
    glm::vec3 edge1 = point1 - point0;
    glm::vec3 edge2 = point2 - point0;

    normal = glm::cross(edge1, edge2);
}

bool Triangle::Collistion(const Ray* ray, glm::vec3& intersectionPoint, float& dist) {
    const float EPSILON = 0.0000001f;

    if (glm::dot((*ray).getDir(), normal) > -EPSILON) {// If the scalarproduct betwen the ray and normal is positiv
        return false;    
    }
    // Time for the Möller Trumbore algorithm 
    // ps = ray orig
    // v0 = point0
    // v1 = point1
    // v2 = point2
    // Barycentric coordinates Triangel(u, v) with u >= 0, v >= 0 and u + v <= 1.
    glm::vec3 T = (*ray).getOrig() - point0;
    glm::vec3 E1 = point1 - point0;
    glm::vec3 E2 = point2 - point0;
    glm::vec3 D = (*ray).getDir();
    glm::vec3 P = glm::cross(D, E2);
    glm::vec3 Q = glm::cross(T, E1);

    float u = (glm::dot(P, T) / glm::dot(P, E1));
    float v = (glm::dot(Q, D) / glm::dot(P, E1));

    if (u < 0.0f || v < 0.0f || u + v > 1.0f) {// Maybe use EPSILON?
        return false;
    }
        float t = (glm::dot(Q, E2) / glm::dot(P, E1));

        intersectionPoint = (*ray).getOrig() + t * (*ray).getDir(); // Changes the value on the vec3

    return true;
}
