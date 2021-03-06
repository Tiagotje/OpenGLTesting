#pragma once
#include <glad/glad.h>
#include "shape.h"
#include "texture.h"
#include "shader.h"


class Cube : public Shape
{
	static unsigned int VAO;
	static bool ready;
public:
	Cube(glm::vec3 loc, glm::quat rot, Shader s, Tex2D t);
	Cube(glm::vec3 loc, glm::quat rot, Shader s, glm::vec3 color);
	Cube();
	static void init();
	void draw(glm::mat4 proj, glm::mat4 view);
};