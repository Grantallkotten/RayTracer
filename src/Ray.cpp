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
      color *= 0.8;
      color += reflectionLight(scene, prevRay, deathProbability) * 0.2;
      break;
  case Material::translucence:
      color = reflectionLightTranslucence(scene, prevRay, deathProbability);
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
    }

    float cosOmega_i = std::sqrt(1.0f - y_i);
    float sinOmega_i = std::sqrt(y_i);
    float phi_i = 2.0f * _PI * y_i;
    // r = 1
    // phi = phi
    // theta = omega
    // cos^2 = 1 - sin^2 
    // See Lecture 2
    float x0 = sinOmega_i * std::cos(phi_i);
    float y0 = sinOmega_i * std::sin(phi_i);
    float z0 = cosOmega_i;

    glm::vec3 e1;// Local axis
    glm::vec3 e2;// Local axis
    glm::vec3 e3;// Local axis

    creatLocalAxes(e1, e2, e3, obj->getNormal(end), dir);

    glm::vec3 newDir(
        x0 * e1.x + y0 * e2.x + z0 * e3.x,
        x0 * e1.y + y0 * e2.y + z0 * e3.y,
        x0 * e1.z + y0 * e2.z + z0 * e3.z);

    Ray newRay(end, newDir);
    ColorDBL inderectLight = newRay.castRay(scene, this, deathProbability)*0.6f;
    return inderectLight;
}

ColorDBL Ray::reflectionLight(Scene* scene, Ray* prevRay, float deathProbability) {
    glm::vec3 normal = obj->getNormal(end);
    
    glm::vec3 nextDir = glm::reflect(dir, normal);//dir - 2.0f * glm::dot(dir, normal) * normal;//I−2*dot(I,N)*N
    Ray nextRay = Ray(end, nextDir);

    return nextRay.castRay(scene, this, deathProbability);
}


ColorDBL Ray::reflectionLightTranslucence(Scene* scene, Ray* prevRay, float deathProbability) {
    // Schlick's law and Snell's will be used
    float n1 = 1.0f; // Air index = 1
    float n2 = 1.5f; // Glass index = 1.5
    glm::vec3 normal = glm::normalize(obj->getNormal(end));
    glm::vec3 dirLight = glm::normalize(dir);

    float cosTheta_in = glm::dot(normal, dirLight);// - dirLight


    if (cosTheta_in < 0.0f) {
        cosTheta_in = -cosTheta_in;
    }
    else {
        normal = -normal;
        std::swap(n1, n2);
    }
        //Schlicks law
        // R = R0 + (1 - R0)(1 + cos(teta))^5
        // R0 = ((n_in - n_out)/(n_in + n_out))^2
        // cos(teta) = dot(N,I)

        float R0 = pow(((n2 - n1) / (n1 + n2)), 2);
        float reflectCofR = R0 + (1 - R0) * pow(1.0f - cosTheta_in, 5);
        float transmissionCofT = 1.0f - reflectCofR;
        float cosTheta_out = 1.0f - pow((n1 / n2), 2.0f) * (1.0f - pow(cosTheta_in, 2));
     
        glm::vec3 dirR = glm::reflect(dirLight, normal);// = dir - 2.0f * glm::dot(dir, normal) * normal
        // Snells law gives us the T direction: n1/n2 * I + (n1/n2 - cos(teta_in) - cos(teta_out))*N
        // cos(teta_in) = dot(N,I)
        // Snells law: 
        // sin(teta_out) = n1/n2 * sqrt(1 - cos^2(teta_in))
        // 1 - cos^2(teta_out) = ((n1/n2)^2 * (1 - cos^2(teta_in))
        // cos(teta_out) = sqrt(1 - ((n1/n2)^2 * (1 - cos^2(teta_in)))
        glm::vec3 dirT = (n1 / n2) * dirLight + ((n1 / n2) * cosTheta_in - sqrt(cosTheta_out))*normal; // - first (n1 + n2)

        Ray nextRayT = Ray(end, dirT, inObject);
        Ray nextRayR = Ray(end, dirR, !inObject);

        ColorDBL colorT = nextRayT.castRay(scene, this, deathProbability) * transmissionCofT;
        ColorDBL colorR = nextRayR.castRay(scene, this, deathProbability) * reflectCofR;// multiplikationen ger inte rätt
        // We want low reflect

        float r = ((float)rand() / (RAND_MAX));

        if (r < reflectCofR) {
            return colorR;
        }
        return colorT;
    
     
}

void creatLocalAxes(glm::vec3& e1, glm::vec3& e2, glm::vec3& e3, const glm::vec3& normal, const glm::vec3& dir) {
    e3 = normal;
    e1 = glm::normalize(-dir + glm::dot(normal, dir) * normal);// The reference direction is given  by the projection of dir onto the surface
    e2 = glm::cross(e3, e1);
}
 

bool Ray::ShadowRay(Scene* scene, Material::MaterialProperty& objMaterialType) {
	// x is on the object and y_i a randome point on the lamp
	float dist_x_to_yi = glm::length(dir);
	float dist_x_to_ip;

    CollisionInfo ci;
	for (Object* obj : scene->Objects) {
		if (obj->Collision(this, ci)) {
			dist_x_to_ip = glm::length(ci.point - orig);

			if (dist_x_to_ip < dist_x_to_yi) {
                objMaterialType = obj->getMaterial().getMaterialProperty();
				return false;
			}
		}
	}
	return true;
}
