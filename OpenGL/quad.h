#pragma once
#include <glad/glad.h>
#include "shape.h"
#include "texture.h"
#include "shader.h"

class Quad : public Shape
{
	static unsigned int VAO;
	static bool ready;
public:
	Quad(glm::vec3 loc, glm::quat rot, Shader s, Tex2D t);
	Quad(glm::vec3 loc, glm::quat rot, Shader s, glm::vec3 color);
	Quad();
	static void init();
	void draw(glm::mat4 proj, glm::mat4 view);
};