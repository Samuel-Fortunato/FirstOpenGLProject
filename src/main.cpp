#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shader_s.h"
#include"stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* setup_window(int windowWidth, int windowHeight, const char* windowTitle);
void process_input(GLFWwindow* window);
void setup_vertex_data(unsigned int* VBO, unsigned int* VAO, unsigned int* EBO);

// Settings
int window_width = 1080;
int window_height = 720;
const char* window_title = "OpenGL Test";

// Vertices
float vertices[] = {
	// positions				// colors					// texture coords
	0.5f, 0.5f, 0.0f,			1.0f, 0.0f, 0.0f,			1.0f, 1.0f,	// top right
	0.5f, -0.5f, 0.0f,			0.0f, 1.0f, 0.0f,			1.0f, 0.0f,	// bottom right
	-0.5f, -0.5f, 0.0f,			0.0f, 0.0f, 1.0f,			0.0f, 0.0f,	// bottom left
	-0.5f, 0.5f, 0.0f,			1.0f, 1.0f, 0.0f,			0.0f, 1.0f	// top left

};
unsigned int indices[] = { // note that we start from 0!
	0, 1, 3,
	1, 2, 3
};

int main() {
	// INITIALIZE WINDOW
	GLFWwindow* window = setup_window(window_width, window_height, window_title);
	if (window == nullptr)
	{		// Error check
		return -1;
	}
	
	// CREATE SHADER
	Shader ourShader("src/shader.vert", "src/shader.frag");

	// SET UP VERTEX DATA
	unsigned int VBO;	// VBO = Vertex buffer object
	unsigned int VAO;	// VAO = Vertex array object	
	unsigned int EBO;	// EBO = Element buffer object
	setup_vertex_data(&VBO, &VAO, &EBO);

	// TEXTURES
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// wrapping / filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("resources/container.jpg", &width, &height, &nrChannels, 0);
	// error check
	if (data)
	{
		// generate texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	// -----------------------------------MAIN WHILE LOOP------------------------------------------
	// --------------------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);

		// Clear screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();

		// Render the triangle
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap buffers and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

GLFWwindow* setup_window(int window_width, int window_height, const char* window_title) {
	if (!glfwInit())		// Error check
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return nullptr;
	};

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_title, nullptr, nullptr);
	if (window == nullptr)		// Error check
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))		// Error check
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}

	glViewport(0, 0, window_width, window_height);

	// Automatically resize the window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
void setup_vertex_data(unsigned int* VBO, unsigned int* VAO, unsigned int* EBO) {
	glGenBuffers(1, VBO);
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, EBO);

	// Bind VAO
	glBindVertexArray(*VAO);
	// Copy vertices to a buffer
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Copy index array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// SET VERTEX ATTRIBUTE POINTERS
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coords attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}
