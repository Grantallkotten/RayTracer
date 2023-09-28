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
  double lightContribution = 0.0;
  color = obj->getMaterial().getColor();

    // Mirror dont need to send shadowrays
    if(obj->getMaterial().getMaterialProperty() == Material::specularity){ return color; }

    for (LightSource *aLightSource : scene->LightSources) {
      lightContribution =
          aLightSource->CheckShadowRays(scene, obj, ci.point);
      // @TODO sätt lightContribution på färgen av objektet
      color *= lightContribution;
    }

    if (((double)rand() / (RAND_MAX)) <= deathProbability) {
    return color; //@TODO * imortance sen och räkna med speculäritet
  }
  
  switch (obj->getMaterial().getMaterialProperty()){
  case Material::specularity:
      /*
      glm::vec3 nextDir = dir - 2.0f * glm::dot(dir, ci.normal) * ci.normal;//I−2*dot(I,N)*N
      Ray* nextRay = new Ray(ci.point, nextDir);
      ColorDBL nextReturncolor = castRay(scene, nextRay, deathProbability);
      returnColor = nextReturncolor;// = because it is a mirror
      */
      break;
  case Material::translucence:
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
      break;

  case Material::diffusion:
      color += inderectLight(scene, prevRay, deathProbability);
      break;

  default:
	  break;
  }
  
  //@TODO Rekursiv formel

  return color;
}

ColorDBL Ray::inderectLight(Scene* scene, Ray* prevRay, float deathProbability) {

    float y_i = ((float)rand() / (RAND_MAX));

    if (y_i < deathProbability) {
        return ColorDBL(0.0f, 0.0f, 0.0f);
        // Ray Should die
    }

    float omega_i = std::acos(std::sqrt(1 - y_i));
    float phi_i = 2.0f * _PI * y_i;
    // r = 1
    // phi = phi
    // theta = omega
    // See Lecture 2
    float x0 = std::sin(phi_i) * std::cos(omega_i);
    float y0 = std::sin(phi_i) * std::sin(omega_i);
    float z0 = std::cos(phi_i);

    glm::vec3 e1 = obj->getNormal(end);// Local axis
    glm::vec3 e2;// Local axis
    glm::vec3 e3;// Local axis

    creatLocalAxes(e1, e2, e3);

    glm::vec3 newDir;
    newDir.x = x0 * e1.x + y0 * e2.x + z0 * e3.x;
    newDir.y = x0 * e1.y + y0 * e2.y + z0 * e3.y;
    newDir.z = x0 * e1.z + y0 * e2.z + z0 * e3.z;

    Ray newRay(end, newDir);
    return getColor() * newRay.castRay(scene, prevRay, deathProbability);
}

void creatLocalAxes(glm::vec3& e1, glm::vec3& e2, glm::vec3& e3) {
    // Generate a random vector to start the process
    glm::vec3 arbitrary_vector(1.0f, 1.0f, 1.0f);

    // Gram-Schmidt process to orthogonalize the vectors
    e2 = glm::normalize(arbitrary_vector - glm::dot(arbitrary_vector, e1) * e1);
    e3 = glm::normalize(glm::cross(e1, e3));
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
