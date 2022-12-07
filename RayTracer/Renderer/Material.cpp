#include "Material.h"

bool Lambertian::Scatter(const Ray& ray, const RaycastHit& hit, color3& attenuation, Ray& scattered) const
{
    glm::vec3 direction = glm::normalize(hit.normal + randomInUnitSphere());
    scattered = { hit.point, direction };
    attenuation = m_albedo;

    return true;
}
