#include "shape.h"
#include "texture.h"
#include "shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#define GLM_ENABLE_EXPERIMENTAL true
#include "glm/gtx/quaternion.hpp"

Shape::Shape() {}

Shape::Shape(glm::vec3 loc, glm::quat rot, Shader s)
{
	location = loc;
	model = glm::mat4(1.0f);
	model = glm::translate(model, location);
	shader = s;
}

void Shape::rotate(float angle, glm::vec3 direction)
{
	model = glm::rotate(model, angle, direction);
}