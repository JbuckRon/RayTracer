#pragma once
#include "Object.h"

class Sphere : public Object
{
public:
	Sphere() = default;
	Sphere(const glm::vec3& center, float radius, std::unique_ptr<Material> material) :
		Object{ std::move(material) },
		m_center{ center },
		m_radius{ radius }
	{
	}
	bool Hit(const Ray& r, float min, float max, RaycastHit& hit) override;
private:
	glm::vec3 m_center{ 0, 0, 0 };
	float m_radius = 0;
};