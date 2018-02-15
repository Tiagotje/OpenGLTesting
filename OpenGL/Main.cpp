#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.h"
#include "texture.h"
#include "shape.h"
#include "cube.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float xOffset = 0.0f;
float yOffset = 0.0f;
float speed = 0.008;


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

														
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Wow Swag", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);


	Shader shader("shader.vs", "shader.fs"); 

	Tex2D tex1("awesomeface.png");

	shader.use();
	shader.setInt("texture1", tex1.getID());

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	Cube cubes[10];

	for (int i = 0; i < 10; i++) {
		glm::quat rot = glm::angleAxis(glm::radians(20.0f*i), glm::vec3(1.0f, 0.3f, 0.5f));
		cubes[i] = Cube(cubePositions[i], rot, shader, tex1);
	}

	//handle Textures

	double lastTime = glfwGetTime();
	int frameCount = 0;

	glfwSwapInterval(1);
	int FPS = 60;

	glm::mat4 proj(1.0f), view(1.0f), model(1.0f);




	// render loop
	while (!glfwWindowShouldClose(window)){
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

		tex1.use();
		shader.use();

		// create transformations
		glm::mat4 view(1.0f);
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		// pass transformation matrices to the shader
		shader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, (float)sin(glfwGetTime())));
		view = glm::rotate(view, (float)glfwGetTime()/3.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		shader.setMat4("view", view);


		
		for (unsigned int i = 0; i < 10; i++)
		{
			//cubes[i].rotate(glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
			cubes[i].draw();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetTime() - lastTime >= 1.0) {
			std::cout << "FPS: " << frameCount << std::endl;
			FPS = frameCount;
			speed = 1.0f / FPS;
			lastTime = glfwGetTime();
			frameCount = 0;
		}
		else {
			frameCount++;
		}
	}

	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		yOffset -= speed;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		yOffset += speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		xOffset -= speed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		xOffset += speed;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}