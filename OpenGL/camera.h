#pragma once
#include "glm/glm.hpp"

class Camera
{
private:
	glm::vec3 pos, target, up;
public:
	Camera();
	Camera(glm::vec3 p, glm::vec3 t, glm::vec3 u);
	Camera(glm::vec3 p, glm::vec3 t) : Camera(p, t, glm::vec3(0.0f, 1.0f, 0.0f)) {};
	glm::mat4 view();
	void move(glm::vec3 v);
	void moveTo(glm::vec3 v);
};