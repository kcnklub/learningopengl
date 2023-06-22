#include <glad/glad.h> // this has to be included before adding glfw3.h
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	// initializing and configuring OpenGL
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "failed to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fajiled to initialize GLAD" << std::endl;
		return -1;
	}

	int numberOfAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numberOfAttributes);
	std::cout << "Max number of vertex attribs supported: " << numberOfAttributes << std::endl;

	Shader shader("./vertexshader.vs", "./fragmentshader.fs");

	float firstTriangle[] = {
		// positions          // colors
		-0.5f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
		-0.25f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f
	};

	float secondTriangle[] = {
		0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.25f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	// Generate vaos
	GLuint vaos[2];
	glGenVertexArrays(2, vaos);

	// Generate vbos
	GLuint vbos[2];
	glGenBuffers(2, vbos);

	glBindVertexArray(vaos[0]); 
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(vaos[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		// input handling
		processInput(window);

		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the triangle;
		shader.use();
		glBindVertexArray(vaos[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(vaos[1]); 
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, vaos);
	glDeleteBuffers(2, vbos);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "sizing to w:" << width << " h:" << height << std::endl;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
