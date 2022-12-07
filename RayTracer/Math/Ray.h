#pragma once
#include "glm/glm.hpp"
#include "../Math/MathUtils.h"

struct Ray
{
	Ray() = default;
	Ray(const glm::vec3& origin, const glm::vec3& direction) : origin{ origin }, direction{ direction } {}
	glm::vec3 GetPoint(float distance) const { return origin + (direction * distance); }


	glm::vec3 origin = { 0, 0, 0 };
	glm::vec3 direction = { 0, 0, 0 };
};

struct RaycastHit
{
	float distance = 0;
	glm::vec3 point = { 0, 0, 0 };
	glm::vec3 normal = { 0, 0, 0 };

	class Material* material{ nullptr };
};