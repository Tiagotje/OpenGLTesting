#pragma once
#include <glad/glad.h>
#include "shape.h"
#include "texture.h"
#include "shader.h"

//I know that I should write this in a cube.cpp file,
//but srsly it's only 1 function and I'm not even getting
//paid for this.

class Cube : public Shape
{
	static unsigned int VAO, VBO;
	Tex2D texture;

public:
	Cube(glm::vec3 loc, glm::quat rot, Shader s, Tex2D t);

	
	Cube() {};

	static void init();

	void draw();
};