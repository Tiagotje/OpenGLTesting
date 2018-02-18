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
	Tex2D texture;
	glm::vec3 color;
	bool textured;
public:
	glm::mat4 model;
	glm::vec3 location;

	Shape();
	Shape(glm::vec3 loc, glm::quat rot, Shader s);
	Shape(glm::vec3 loc, glm::quat rot, Shader s, Tex2D tex);
	Shape(glm::vec3 loc, glm::quat rot, Shader s, glm::vec3 col);

	Shape(glm::vec3 loc, float angle, glm::vec3 axis, Shader s) :
		Shape(loc, glm::angleAxis(angle, axis), s)
	{};

	void rotate(float angle, glm::vec3 direction);
	void scale(glm::vec3 factors);
	virtual void draw(glm::mat4 proj, glm::mat4 view) = 0;
};