#include "../include/Ray.h"
#include "../include/Object.h"
#include "../include/Scene.h"
#include "../include/Sphere.h"  // Include any other necessary headers.

#include <limits>
#include <random>  // Include the header for better random number generation.

const float PI = 3.14159265358979323846f;
const float EPSILON = 0.00001f;

ColorDBL Ray::castRay(Scene* scene, Ray* prevRay, float deathProbability) {
    prev = prevRay;
    float minDist = std::numeric_limits<float>::max();
    bool hitsObject = false;
    CollisionInfo ci;

    for (Object* aObject : scene->Objects) {
        CollisionInfo ciNew;
        if (aObject->Collision(this, ciNew)) {
            hitsObject = true;
            float newDist = glm::length(ciNew.point - orig);

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

    for (LightSource* aLightSource : scene->LightSources) {
        lightContribution = aLightSource->CheckShadowRays(scene, obj, ci.point);
        color *= lightContribution;
    }

    switch (obj->getMaterial().getMaterialProperty()) {
    case Material::specularity:
        color = reflectionLight(scene, prevRay, deathProbability);
        break;
    case Material::glossy:
        color = 0.8 * color + 0.2 * reflectionLight(scene, prevRay, deathProbability);
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

    return color;
}

ColorDBL Ray::inderectLight(Scene* scene, Ray* prevRay, float deathProbability) {
    float y_i = ((float)rand() / (RAND_MAX));

    if (y_i < deathProbability) {
        return ColorDBL(0.0f, 0.0f, 0.0f);
    }

    float cosOmega_i = std::sqrt(1.0f - y_i);
    float sinOmega_i = std::sqrt(y_i);
    float phi_i = 2.0f * PI * y_i;
    float x0 = sinOmega_i * std::cos(phi_i);
    float y0 = sinOmega_i * std::sin(phi_i);
    float z0 = cosOmega_i;

    glm::vec3 e1, e2, e3;
    creatLocalAxes(e1, e2, e3, obj->getNormal(end), dir);

    glm::vec3 newDir(
        x0 * e1.x + y0 * e2.x + z0 * e3.x,
        x0 * e1.y + y0 * e2.y + z0 * e3.y,
        x0 * e1.z + y0 * e2.z + z0 * e3.z);

    Ray newRay(end, newDir);
    ColorDBL indirectLight = newRay.castRay(scene, this, deathProbability);
    return indirectLight;
}

ColorDBL Ray::reflectionLight(Scene* scene, Ray* prevRay, float deathProbability) {
    glm::vec3 normal = obj->getNormal(end);
    glm::vec3 nextDir = glm::reflect(dir, normal);
    Ray nextRay(end, nextDir);
    return nextRay.castRay(scene, this, deathProbability);
}

ColorDBL Ray::reflectionLightTranslucence(Scene* scene, Ray* prevRay, float deathProbability) {
    float n1 = 1.0f;  // Air index = 1
    float n2 = 1.5f;  // Glass index = 1.5
    glm::vec3 normal = glm::normalize(obj->getNormal(end));
    glm::vec3 dirLight = glm::normalize(dir);

    float cosTheta_in = glm::dot(normal, dirLight);

    if (cosTheta_in < 0.0f) {
        cosTheta_in = -cosTheta_in;
    }
    else {
        normal = -normal;
        std::swap(n1, n2);
    }

    // Calculate the refraction direction using Snell's Law
    float ratio = n1 / n2;
    float cosTheta_out = sqrt(1.0f - pow(ratio, 2.0f) * (1.0f - pow(cosTheta_in, 2.0f)));
    glm::vec3 dirT = ratio * dirLight + (ratio * cosTheta_in - cosTheta_out) * normal;

    // Calculate the Fresnel reflection coefficient (Schlick's approximation)
    float R0 = pow((n1 - n2) / (n1 + n2), 2.0f);
    float reflectCofR = R0 + (1.0f - R0) * pow(1.0f - cosTheta_in, 5.0f);
    float refractionCofT = 1.0f - reflectCofR;


    // Determine if total internal reflection occurs
    if (cosTheta_out < 0.0f) {
        return reflectionLight(scene, prevRay, deathProbability);
    }
    /*
    // Determine whether to reflect or refract based on Fresnel reflection probability
    float r = ((float)rand() / (RAND_MAX));

    if (r < reflectCofR) {
        return reflectionLight(scene, prevRay, deathProbability);
    }
    */
    Ray nextRayT = Ray(end, dirT, !inObject);
    Ray nextRayR = Ray(end, glm::reflect(dirLight, normal), !inObject);

    ColorDBL colorT = nextRayT.castRay(scene, this, deathProbability);
    ColorDBL colorR = nextRayR.castRay(scene, this, deathProbability);


    return colorT* refractionCofT + colorR * reflectCofR*1.2f;
}



void Ray::creatLocalAxes(glm::vec3& e1, glm::vec3& e2, glm::vec3& e3, const glm::vec3& normal, const glm::vec3& dir) {
    e3 = normal;
    e1 = glm::normalize(-dir + glm::dot(normal, dir) * normal);
    e2 = glm::cross(e3, e1);
}

bool Ray::ShadowRay(Scene* scene, Material::MaterialProperty& objMaterialType) {
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
