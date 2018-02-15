#pragma once
#include <glad/glad.h>
#include "shape.h"
#include "texture.h"
#include "shader.h"


class Cube : public Shape
{
	static unsigned int VAO;
	Tex2D texture;
	static bool ready;
public:
	Cube(glm::vec3 loc, glm::quat rot, Shader s, Tex2D t);
	Cube();
	static void init();
	void draw(glm::mat4 proj, glm::mat4 view);
};