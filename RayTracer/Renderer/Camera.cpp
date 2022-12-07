#include "Camera.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectRatio) :
	m_fov{ fov },
	m_aspectRatio{ aspectRatio }
{
	LookAt(eye, target, up);
}

void Camera::LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
	m_eye = eye;
	// set the camera axis vectors (forward, right, up)
	//
	// forward is the vector (target -> eye)
	m_forward = glm::normalize(eye - target);
	// right is the cross product of the up and forward vector
	// up x forward = vector perpendicular which is the right vector
	m_right = glm::normalize(glm::cross(up, m_forward));
	// up is the cross product of the forward and right vector
	m_up = glm::cross(m_forward, m_right);
	CalculateViewPlane();
}

Ray Camera::PointToRay(const glm::vec2& point) const
{
	Ray ray;
	ray.origin = m_eye;
	// calculate direction from point * view plane
	ray.direction = m_lowerLeft + (point.x * m_horizontal) + (point.y * m_vertical) - m_eye;
	return ray;
}

void Camera::CalculateViewPlane()
{
	// convert fov angle to radians
	float theta = glm::radians(m_fov);
	// calculate the width / height of the view plane
	float halfHeight = tan(theta * 0.5f);
	float halfWidth = halfHeight * m_aspectRatio;
	float height = halfHeight * 2;
	float width = halfWidth * 2;
	// calculate horizontal view plane vector (width * right vector)
	m_horizontal = width * m_right;
	// calculate vertical view plane vector (height * up vector)
	m_vertical = height * m_up;
	// calculate lower left location of the view plane
	m_lowerLeft = m_eye - (m_horizontal * 0.5f) - (m_vertical * 0.5f) - m_forward;
}
