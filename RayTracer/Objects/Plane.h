#pragma once
#include "Object.h"
class Plane : public Object
{
public:
	Plane(const glm::vec3& center, const glm::vec3& normal, std::unique_ptr<Material> material) :
		Object{ std::move(material) },
		m_center{ center },
		m_normal{ normal }
	{
	}
	bool Hit(const Ray& ray, float min, float max, RaycastHit& hit) override;
private:
	glm::vec3 m_center{ 0, 0, 0 };
	glm::vec3 m_normal{ 0, 0, 0 };
};
