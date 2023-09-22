#pragma once
#include "Object.h"
#include "Material.h"


class Sphere : public Object {
private:
	glm::vec3 centerPoint;
	float radius;
	Material material;

public:
	Sphere(glm::vec3 centerPoint = glm::vec3(8.0f, 0.0f, 0.0f), float radius = 1.0f, Material material = Material(Material::diffusion, ColorDBL(0.3, 0.2, 0.2))) : centerPoint{ centerPoint }, radius{ radius }, material{ material }{
	
	}

	glm::vec3 getNormal(glm::vec3 point) override { return glm::normalize(point - centerPoint); }

	Material getMaterial() override { return material; }

	bool Collision(Ray* ray, glm::vec3& intersectionPoint) override;

	glm::vec3 getCenterPoint() { return centerPoint; }

	float getRadius() { return radius; }

};

