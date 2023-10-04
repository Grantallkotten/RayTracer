#include "../include/Ray.h"
#include "../include/Object.h"
#include "../include/Scene.h"
class LightSource;

#define _PI 3.14159265358979323846f  // Pi


ColorDBL Ray::castRay(Scene *scene, Ray *prevRay, float deathProbability) {
  // Är prevRay nödvändig?
  prev = prevRay;
  float minDist = std::numeric_limits<float>::max();
  float newDist = std::numeric_limits<float>::max();
  bool hitsObject = false;

  CollisionInfo ci, ciNew;

  for (Object *aObject : scene->Objects) {
    if (aObject->Collision(this, ciNew)) {
      hitsObject = true;
      newDist = glm::length(ciNew.point - orig);

      if (newDist <= minDist) {
        minDist = newDist;
        ci = ciNew;
        obj = aObject;
        end = ci.point;
      }
    }
  }

  if (!hitsObject) {
    return scene->SKYBOXCOLOR;
  }
  color = obj->getMaterial().getColor();
  double lightContribution = 0.0;

  for (LightSource *aLightSource : scene->LightSources) {
    lightContribution = aLightSource->CheckShadowRays(scene, obj, ci.point);
    color *= lightContribution;
  }
#if 1
  switch (obj->getMaterial().getMaterialProperty()){
  case Material::specularity:
      color = reflectionLight(scene, prevRay, deathProbability);

      break;
  case Material::glossy:
      color *= 0.2;
      color += reflectionLight(scene, prevRay, deathProbability) * 0.8;
      break;
  case Material::translucence:
     
      break;
  case Material::diffusion:
      color += inderectLight(scene, prevRay, deathProbability) * obj->getMaterial().getColor();
      break;
  case Material::light:
      break;
  default:
	  break;
  }
#endif
  return color;
}

ColorDBL Ray::inderectLight(Scene* scene, Ray* prevRay, float deathProbability) {

    float y_i = ((float)rand() / (RAND_MAX));

    if (y_i < deathProbability) {
        return ColorDBL(0.0f, 0.0f, 0.0f);
        // Ray Should die
    }

    float omega_i = std::acos(std::sqrt(1.0f - y_i));
    float phi_i = 2.0f * _PI * y_i;
    // r = 1
    // phi = phi
    // theta = omega
    // See Lecture 2
    float x0 = std::sin(phi_i) * std::cos(omega_i);
    float y0 = std::sin(phi_i) * std::sin(omega_i);
    float z0 = std::cos(omega_i);

    glm::vec3 e1;// Local axis
    glm::vec3 e2;// Local axis
    glm::vec3 e3;// Local axis

    creatLocalAxes(e1, e2, e3, obj->getNormal(end));

    glm::vec3 newDir;
    newDir.x = x0 * e1.x + y0 * e2.x + z0 * e3.x;
    newDir.y = x0 * e1.y + y0 * e2.y + z0 * e3.y;
    newDir.z = x0 * e1.z + y0 * e2.z + z0 * e3.z;

    Ray newRay(end, newDir);
    ColorDBL inderectLight = newRay.castRay(scene, this, deathProbability)*0.8f;
    return inderectLight;
}

ColorDBL Ray::reflectionLight(Scene* scene, Ray* prevRay, float deathProbability) {
    glm::vec3 objNormal = obj->getNormal(end);
    
    glm::vec3 nextDir = dir - 2.0f * glm::dot(dir, objNormal) * objNormal;//I−2*dot(I,N)*N
    Ray nextRay = Ray(end, nextDir);

    return nextRay.castRay(scene, this, deathProbability);

}


ColorDBL Ray::reflectionLightTranslucence(Scene* scene, Ray* prevRay, float deathProbability) {
    /*
     // Probability of bouncing
     if (true) {
         glm::vec3 nextDir = dir - 2.0f * glm::dot(dir, ci.normal) * ci.normal;//I−2×(I⋅N)×N
         Ray* nextRay = new Ray(ci.point, nextDir);
         ColorDBL nextReturncolor = castRay(scene, nextRay, deathProbability);
         returnColor = nextReturncolor;// = because it is a mirror reflection on glass
     }
     // Probability of entering the material
     else {
         // R = n1/n2 * ( I + (cos(v1) - cos(v2) ) * N )
         // cos(θ) = norm(dot(I,N))
         // Glass n = 1.5
         // Air n = 1
         float n1 = 1.0f;
         float n2 = 1.5f;
         glm::vec3 I = glm::normalize(dir);
         glm::vec3 N = ci.normal;
         //@TODO Vad gör vi om vi är påväg ut från glas, då är inte n1 luft och n2 glas
         //@TODO Ändra så normalerna är baklänges i check kollision för att det ska kunna ske en kollision på väg ut från ett glas objekt
         float r = n1 / n2;
         glm::vec3 nextDir = r * dir + (r * glm::dot(I, N) - std::sqrt(1.0f - r * r * (1.0f - glm::dot(I, N) * glm::dot(I,N) ))) * N;
         Ray* nextRay = new Ray(ci.point, nextDir);
         ColorDBL nextReturncolor = castRay(scene, nextRay, deathProbability);
         returnColor += nextReturncolor;// @TODO Ska det va +=??
     }
     */
    return ColorDBL();
}

void creatLocalAxes(glm::vec3& e1, glm::vec3& e2, glm::vec3& e3, const glm::vec3& normal) {
   /* glm::vec3 n = glm::normalize(normal);

    // Choose a reference vector that is not collinear with the normal
    glm::vec3 refVector(0.0f, 1.0f, 0.0f);  // A common choice for a reference vector

    // Check if the reference vector is parallel to the normal
    if (glm::dot(n, refVector) > 0.99f) {
        // If it's too close to being parallel, choose a different reference vector
        refVector = glm::vec3(1.0f, 0.0f, 0.0f);  // Use a different reference vector
    }

    // Calculate the local x-axis as the normalized normal vector
    e1 = n;

    // Calculate the local z-axis as the normalized cross product of the normal and the reference vector
    e3 = (glm::cross(n, refVector));
    */
    // Calculate the local y-axis as the normalized cross product of the local z-axis and the local x-axis
    e1 = (normal);
    e2 = glm::vec3(e1.z, 0.0f, -e1.x);
    if (glm::length(e2) < 0.01f) {
        // If the normal is (0, 1, 0) 
        e2 = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    e3 = glm::cross(e1, e2);
    //std::cout << "  e1: " << glm::length(e1) << " e2: " << glm::length(e2) << " e3: " << glm::length(e3) << "        ";
    /*
    glm::vec3 arbitrary_vector = (glm::abs(glm::dot(normal, glm::vec3(1.0f, 0.0f, 0.0f))) < 0.1f) ? glm::vec3(1.0f, 0.0f, 0.0f) : glm::vec3(0.0f, 1.0f, 0.0f); 
    e3 = glm::normalize(normal);
    e1 = glm::normalize(glm::cross(arbitrary_vector, e3));
    e2 = glm::normalize(glm::cross(e3, e1));
    */
    /*
    e3 = glm::normalize(e3);
    e1 = glm::normalize(-e1 + glm::dot(e3, e1) * e3);
    e2 = glm::normalize(glm::cross(e3, e1));
    */
}
 

bool Ray::ShadowRay(Scene* scene) {
	// x is on the object and y on the lamp
	float dist_x_to_yi = glm::length(dir);
	float dist_x_to_ip;

    CollisionInfo ci;
	for (Object* obj : scene->Objects) {
		if (obj->getMaterial().getMaterialProperty() != Material::translucence && obj->Collision(this, ci)) {
			dist_x_to_ip = glm::length(ci.point - orig);

			if (dist_x_to_ip < dist_x_to_yi) {

				return false;
			}
		}
	}
	return true;
}
