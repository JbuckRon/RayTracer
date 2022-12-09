#include "Scene.h"
#include "Object.h"

color3 Scene::Trace(const Ray& ray, float min, float max, RaycastHit& hit, int depth)
{
    bool rayHit = false;

    float closest = max;

    // get closest ray hit
    for (auto& object : m_objects)
    {
        if (object->Hit(ray, min, closest, hit))
        {
            rayHit = true;
            closest = hit.distance;
        }
    }

    // if ray hit object, scatter (bounce) ray and check for next hit
    if (rayHit)
    {
        Ray scattered;
        color3 attenuation;

        // limit the number of bounces to depth, get color attenuation
        // final color is product of object colors (object->material * object->material * ...)
        if (depth > 0 && hit.material->Scatter(ray, hit, attenuation, scattered))
        {
            return attenuation * Trace(scattered, min, max, hit, depth - 1);
        }
        else
        {
            return hit.material->GetEmissive();
        }
    }
    else
    {
        glm::vec3 direction = glm::normalize(ray.direction);
        float t = (direction.y + 1) * 0.5f;
        return lerp(m_topColor, m_bottomColor, t);
    }
}

void Scene::AddObject(std::unique_ptr<Object> object)
{
	m_objects.push_back(std::move(object));
}
