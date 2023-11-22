#include "Ray.h"
#include "ColorDBL.h"
#include "Object.h"
#include "Scene.h"
#include "Sphere.h" // Include any other necessary headers>
#include "Util.h"

ColorDBL Ray::castRay(Scene *scene, KDTree<Photon> &photons,
                      float deathProbability) {
  bool castNewRay = true;
  float importance = 1.0f;

  while (castNewRay) {
    float minDist = std::numeric_limits<float>::max();
    CollisionInfo ci;

    for (Object *aObject : scene->Objects) {
      CollisionInfo ciNew;
      if (aObject->Collision(this, ciNew)) {
        float newDist = glm::length(ciNew.point - origin);

        if (newDist <= minDist) {
          minDist = newDist;
          ci = ciNew;
          obj = aObject;
          end = ci.point;
        }
      }
    }

    if (minDist == std::numeric_limits<float>::max()) {
      return scene->SKYBOXCOLOR;
    }

    double lightContribution = 0.0;

    for (LightSource *aLightSource : scene->LightSources) {
      lightContribution += aLightSource->CheckShadowRays(scene, obj, ci.point);
    }

    float pdf = 1.0f;
    switch (obj->getMaterial().getProperty()) {
   case reflector:
      reflectionLight();
      break;
   /* case glossy:
      color *= 0.8;
      reflectionLight();
      break;
    case transparent:
      reflectionLightTranslucence();
      break;*/
    case diffusion:
        color += inderectLight(photons, pdf) * lightContribution * importance;
        if (glm::linearRand(0.0f, 0.9999f) < deathProbability) {
            castNewRay = false;
        }
      break;
    case light:
      color += obj->getMaterial().getColor();
      castNewRay = false;
      break;
    default:
        color += inderectLight(photons, pdf) * lightContribution * importance;
        if (glm::linearRand(0.0f, 0.9999f) < deathProbability) {
            castNewRay = false;
        }
      break;
    }
    importance *= pdf;
    //std::cout << pdf << " ";
  }
  return color;
}

ColorDBL Ray::inderectLight(KDTree<Photon> &photons, float& pdf, const float photonRadius) {
  glm::vec3 p = rtu::randomPointOnHemisphere(pdf);

  glm::vec3 e1, e2, e3;
  rtu::creatLocalAxes(e1, e2, e3, obj->getNormal(end), dir);

  dir = glm::vec3(p.x * e1.x + p.y * e2.x + p.z * e3.x,
                  p.x * e1.y + p.y * e2.y + p.z * e3.y,
                  p.x * e1.z + p.y * e2.z + p.z * e3.z);

  origin = end;

  return (obj->getMaterial().getColor() +
      PhotonMapper::calculatePhotonContribution(photons, end,
          photonRadius));
} 

void Ray::reflectionLight() {
  glm::vec3 normal = obj->getNormal(end);
  dir = glm::reflect(dir, normal);
  origin = end;
}

void Ray::reflectionLightTranslucence() {
  float n1 = 1.0f; // Air index = 1
  float n2 = 1.5f; // Glass index = 1.5
  glm::vec3 normal = glm::normalize(obj->getNormal(end));
  glm::vec3 dirLight = glm::normalize(dir);

  float cosTheta_in = glm::dot(normal, dirLight);

  if (cosTheta_in < 0.0f) {
    cosTheta_in = -cosTheta_in;
  } else {
    normal = -normal;
    std::swap(n1, n2);
  }

  // Calculate the refraction direction using Snell's Law
  float ratio = n1 / n2;
  float cosTheta_out =
      sqrt(1.0f - pow(ratio, 2.0f) * (1.0f - pow(cosTheta_in, 2.0f)));

  // Calculate the Fresnel reflection coefficient (Schlick's approximation)
  float R0 = pow((n1 - n2) / (n1 + n2), 2.0f);
  float reflectCofR = R0 + (1.0f - R0) * pow(1.0f - cosTheta_in, 5.0f);

  // Determine if total internal reflection occurs
  if (cosTheta_out < 0.0f) {
    return reflectionLight();
  }

  // Determine whether to reflect or refract based on Fresnel reflection
  // probability
  float r = glm::linearRand(0.0f, 1.0f);

  if (r < reflectCofR)
    return reflectionLight();

  dir = ratio * dirLight + (ratio * cosTheta_in - cosTheta_out) * normal;
  origin = end;
}

bool Ray::ShadowRay(Scene *scene, MaterialProperty &objMaterialType) {
  float dist_x_to_yi = glm::length(dir);
  float dist_x_to_ip;
  CollisionInfo ci;

  for (Object *obj : scene->Objects) {
    if (obj->Collision(this, ci)) {
      dist_x_to_ip = glm::length(ci.point - origin);

      if (dist_x_to_ip < dist_x_to_yi) {
        objMaterialType = obj->getMaterial().getProperty();
        return false;
      }
    }
  }

  return true;
}

void Ray::castPhoton(Scene *scene, Ray *prevRay, KDTree<Photon> &photons) {
  prev = prevRay;
  float minDist = std::numeric_limits<float>::max();
  bool hitsObject = false;
  CollisionInfo ci;

  for (Object *aObject : scene->Objects) {
    CollisionInfo ciNew;
    if (aObject->Collision(this, ciNew)) {
      hitsObject = true;
      float newDist = glm::length(ciNew.point - origin);

      if (newDist <= minDist) {
        minDist = newDist;
        ci = ciNew;
        obj = aObject;
        end = ci.point;
      }
    }
  }
  if (!hitsObject)
    return;
  if (obj->getMaterial().getProperty() == transparent) {
    photonTranslucent(scene, photons);
  } else if (obj->getMaterial().getProperty() == reflector)
    reflectPhoton(scene, photons);
  else {
    color *= obj->getMaterial().getColor();
    Photon photon;
    photon.position = end;
    photon.color = color;
    photon.direction = -glm::normalize(dir);
    photons.insert(photon);
  }
}

void Ray::reflectPhoton(Scene *scene, KDTree<Photon> &photons) {
  glm::vec3 normal = obj->getNormal(end);
  glm::vec3 nextDir = glm::reflect(dir, normal);
  Ray nextRay(end, nextDir);
  nextRay.setColor(color);
  return nextRay.castPhoton(scene, this, photons);
}

void Ray::photonTranslucent(Scene *scene, KDTree<Photon> &photons) {
  float n1 = 1.0f; // Air index = 1
  float n2 = 1.5f; // Glass index = 1.5
  glm::vec3 normal = glm::normalize(obj->getNormal(end));
  glm::vec3 dirLight = glm::normalize(dir);

  float cosTheta_in = glm::dot(normal, dirLight);

  if (cosTheta_in < 0.0f) {
    cosTheta_in = -cosTheta_in;
  } else {
    normal = -normal;
    std::swap(n1, n2);
  }

  // Calculate the refraction direction using Snell's Law
  float ratio = n1 / n2;
  float cosTheta_out =
      sqrt(1.0f - pow(ratio, 2.0f) * (1.0f - pow(cosTheta_in, 2.0f)));
  glm::vec3 dirT = glm::normalize(
      ratio * dirLight + (ratio * cosTheta_in - cosTheta_out) * normal);

  // Calculate the Fresnel reflection coefficient (Schlick's approximation)
  float R0 = pow((n1 - n2) / (n1 + n2), 2.0f);
  float reflectCofR = R0 + (1.0f - R0) * pow(1.0f - cosTheta_in, 5.0f);

  // Determine if total internal reflection occurs
  /* if (cosTheta_out < 0.0f) {
     return reflectPhoton(scene, photons);
   }*/

  // Determine whether to reflect or refract based on Fresnel reflection
  // probability
  float r = ((float)rand() / (RAND_MAX));

  if (r < reflectCofR)
    return reflectPhoton(scene, photons);

  Ray nextRay = Ray(end, dirT, !inObject);
  nextRay.setColor(color);
  return nextRay.castPhoton(scene, this, photons);
}
