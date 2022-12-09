#include "Material.h"
#include "../Math/MathUtils.h"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

bool Lambertian::Scatter(const Ray& ray, const RaycastHit& hit, color3& attenuation, Ray& scattered) const
{
    glm::vec3 target = hit.point + hit.normal + randomInUnitSphere();
    glm::vec3 direction = glm::normalize(target - hit.point);
    scattered = { hit.point, direction };
    attenuation = m_albedo;

    return true;
}

bool Metal::Scatter(const Ray& ray, const RaycastHit& hit, color3& attenuation, Ray& scattered) const
{
    glm::vec3 reflected = reflect(glm::normalize(ray.direction), hit.normal);

    scattered = { hit.point, reflected + randomInUnitSphere() * m_fuzz};

    attenuation = m_albedo;

    return dot(hit.normal, scattered.direction) > 0;
}

bool Dielectric::Scatter(const Ray& ray, const RaycastHit& hit, color3& attenuation, Ray& scattered) const
{
    // set color
    attenuation = m_albedo;

    glm::vec3 out_normal;
    float ni_over_nt;
    float cosine;

    // ray hits inside of surface
    if (glm::dot(ray.direction, hit.normal) > 0)
    {
        // flip hit normal (points inward)
        out_normal = -hit.normal;
        ni_over_nt = m_index;
        cosine = m_index * glm::dot(ray.direction, hit.normal) / ray.direction.length();
    }
    else
    {
        // ray hits outside of surface
        out_normal = hit.normal;
        ni_over_nt = 1.0f / m_index;
        cosine = -glm::dot(ray.direction, hit.normal) / ray.direction.length();
    }

    // get refraction vector
    glm::vec3 refracted;
    float reflectProbability = 1.0f;
    if (refract(ray.direction, out_normal, ni_over_nt, refracted))
    {
        reflectProbability = schlick(cosine, m_index);
    }

    // get reflected vector
    glm::vec3 reflected = reflect(glm::normalize(ray.direction), hit.normal);

    // get reflected or refracted ray
    scattered = (random01() < reflectProbability) ? Ray{ hit.point, reflected } : Ray{ hit.point, refracted };

    return true;
}
