#include <glad/glad.h>
#include "shape.h"
#include "glm/gtc/type_ptr.hpp"
#include "texture.h"
#include "shader.h"
#include "quad.h"

unsigned int Quad::VAO = 0;
bool Quad::ready = false;

Quad::Quad()
{
	Quad::init();
}

Quad::Quad(glm::vec3 loc, glm::quat rot, Shader s, Tex2D t) : Shape(loc, rot, s, t) {
	Quad::init();
}

Quad::Quad(glm::vec3 loc, glm::quat rot, Shader s, glm::vec3 c) : Shape(loc, rot, s, c) {
	Quad::init();
}

void Quad::init()
{
	if (Quad::ready) return;
	Quad::ready = true;
	unsigned int VBO;
	float vertices[] = {
		0.5f, 0.0f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	   -0.5f, 0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	   -0.5f, 0.0f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	   -0.5f, 0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}