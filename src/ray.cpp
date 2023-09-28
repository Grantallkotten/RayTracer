#include "../include/Ray.h"
#include "../include/Object.h"
#include "../include/Scene.h"
class LightSource;

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
      }
    }
  }

  if (!hitsObject) {
    return scene->SKYBOXCOLOR;
  }
  double lightContribution = 0.0;
  ColorDBL returnColor = obj->getMaterial().getColor();

  if (((double)rand() / (RAND_MAX)) <= deathProbability) {

    // Mirror dont need to send shadowrays
    if(obj->getMaterial().getMaterialProperty() == Material::specularity){ return returnColor; }

    for (LightSource *aLightSource : scene->LightSources) {
      lightContribution =
          aLightSource->CheckShadowRays(scene, obj, ci.point);
      // @TODO sätt lightContribution på färgen av objektet
      returnColor *= lightContribution;
    }

    return returnColor; //@TODO * imortance sen och räkna med speculäritet
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
      break;

  default:
	  break;
  }
  
  //@TODO Rekursiv formel

  return ColorDBL(0.0f, 0.0f, 0.2f);
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
