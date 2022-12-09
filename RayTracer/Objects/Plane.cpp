#include "Plane.h"

bool Plane::Hit(const Ray& ray, float min, float max, RaycastHit& hit)
{
	// if dot product (direction and plane normal) is 0 direction is parallel
	float denominator = dot(ray.direction, m_normal);
	if (abs(denominator) < std::numeric_limits<float>::epsilon())
	{
		return false; // direction and plane parallel, no intersection
	}
	float t = glm::dot(m_center - ray.origin, m_normal) / denominator;
	if (t < 0)
	{
		return false; // plane behind ray's origin
	}
	// check if t (distance is within range
	if (t > min && t < max)
	{
		hit.distance = t;
		hit.point = ray.GetPoint(t);
		hit.normal = m_normal;
		hit.material = m_material.get();
		
		//< set the hit distance, point, normaland material
			return true;
	}
	return false;
}
