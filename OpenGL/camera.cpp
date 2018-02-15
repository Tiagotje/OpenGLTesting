#include "camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
{
	pos = glm::vec3(0.0f, 0.0f, 5.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera(glm::vec3 p, glm::vec3 t, glm::vec3 u) 
{
	pos = p;
	target = t;
	up = u;
}

glm::mat4 Camera::view()
{
	return glm::lookAt(pos, target, up);
}

void Camera::move(glm::vec3 v)
{
	pos = pos + v;
}

void Camera::moveTo(glm::vec3 v)
{
	pos = v;
}