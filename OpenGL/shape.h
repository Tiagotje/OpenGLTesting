#pragma once
#include <glad/glad.h>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "texture.h"
#include "shader.h"

class Shape
{
protected:
	Shader shader;
public:
	glm::mat4 model;
	glm::vec3 location;

	Shape();
	Shape(glm::vec3 loc, glm::quat rot, Shader s);


	Shape(glm::vec3 loc, float angle, glm::vec3 axis, Shader s) :
		Shape(loc, glm::angleAxis(angle, axis), s)
	{};

	void rotate(float angle, glm::vec3 direction);
	virtual void draw() = 0;
};