#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.h"
#include "texture.h"
#include "shape.h"
#include "cube.h"
#include "quad.h"
#include "camera.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

float FOV = 45.0F;
int FPS = 4000;
float camHeight = 3;

glm::vec3 lightColor = glm::vec3(0.9f, 0.95f, 0.95f);


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

														
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Wow Swag", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader shader("shader.vs", "shader.fs"); 

	Tex2D tex1("container.jpg", true);

	shader.use();
	shader.setInt("texture1", tex1.getID());
	shader.setVec3("lightcolor", lightColor);


	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  6.0f, -8.0f),
		glm::vec3(-1.5f, 0.5f, -2.5f),
		glm::vec3(-3.8f, 0.5f, -8.3f),
		glm::vec3(2.4f,  0.5f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f,  0.5f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.5f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	Cube cubes[10];

	for (int i = 0; i < 10; i++) {
		cubes[i] = Cube(cubePositions[i], glm::quat(), shader, tex1);
	}


	double lastTime = glfwGetTime();
	int frameCount = 0;
	glfwSwapInterval(0);

	Camera cam1 = Camera();

	glEnable(GL_MULTISAMPLE);

	Quad quad1 = Quad(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(), shader, glm::vec3(0.9f, 0.9f, 0.9f));
	quad1.scale(glm::vec3(1000.0f, 1.0f, 1000.0f));

	// render loop
	while (!glfwWindowShouldClose(window)){
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// also clear the depth buffer now!


		//create projection
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(FOV), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		float camX = sin(glfwGetTime()/5.0f) * 10.0f;	
		float camZ = cos(glfwGetTime()/5.0f) * 10.0f - 0.0f;
		cam1.moveTo(glm::vec3(camX, camHeight, camZ));
		
		shader.use();

		for (unsigned int i = 0; i < 10; i++)
		{
			cubes[i].draw(projection, cam1.view());
		}

		quad1.draw(projection, cam1.view());

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetTime() - lastTime >= 1.0) {
			std::cout << "FPS: " << frameCount << std::endl;
			FPS = frameCount;
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
		FOV += (10.0f/FPS);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		FOV -= (10.0f/FPS);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camHeight += (5.0f / FPS);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camHeight -= (5.0f / FPS);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}